import frida
import typing as t
import time
import subprocess

PW_PATTERN = (
    "08 00 00 00 09 00 00 00 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 00 00 00"
)
ID_PATTERN = (
    "01 00 00 00 0B 00 00 00 0D 00 00 00 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ??"
    " ?? ?? ?? ?? ?? ?? 00 00 00"
)
SCRIPT_SCAN = """

    function handleStart(message) { 
        var ranges = Process.enumerateRanges({protection: 'r--', coalesce: true});
        var range;
        
        function processNext(){

            range = ranges.pop();
            if(!range){
                send("finish");
                return;
            }

            Memory.scan(range.base, range.size, '%s', {
                onMatch: function(address, size){
                        var buf = Memory.readByteArray(address, 34);
                        send("id", buf);
                    }, 
                onError: function(reason){
                        console.log('[!] Error scanning ID: ' + reason);
                    }, 
                onComplete: function(){

                    Memory.scan(range.base, range.size, '%s', {
                        onMatch: function(address, size){
                                var buf = Memory.readByteArray(address, 24);
                                send("pw", buf);
                            }, 
                        onError: function(reason){
                                console.log('[!] Error scanning PW: ' + reason);
                            }, 
                        onComplete: function(){
                                processNext();
                            }
                        });
                    }

                });
                
        }
        
        processNext();
        recv('start', handleStart);
    }

    recv('start', handleStart);
""" % (
    ID_PATTERN,
    PW_PATTERN,
)

FoundID = None
FoundPW = None
breakLoop = False


def on_message(message: t.Dict[str, str], data: bytes):
    global breakLoop, FoundID, FoundPW
    msg = message["payload"]

    if msg == "id":

        id = data[12:].decode("utf-16")
        if id.isprintable():
            print(f"Found id: {id}")
            FoundID = id

    elif msg == "pw":
        pw = data[8:].decode("utf-16")

        if pw.isprintable() and pw != "Password":
            print(f"Found password: {pw}")
            FoundPW = pw

    elif msg == "finish":
        breakLoop = True


def StartTeamviewer(executable: str, timeout: int = 30000) -> t.Tuple[str, str]:
    global breakLoop, FoundID, FoundPW
    process = subprocess.Popen(
        [executable],
        creationflags=subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP,
    )

    session = frida.attach("TeamViewer.exe")
    script = session.create_script(SCRIPT_SCAN)
    script.on("message", on_message)
    script.load()

    begin = time.perf_counter()

    while FoundID == None or FoundPW == None:

        breakLoop = False
        script.post({"type": "start"})

        while breakLoop == False:
            time.sleep(0.1)

        if (time.perf_counter() - begin) >= timeout:
            process.terminate()
            return None
    print(FoundID, FoundPW)
    return FoundID, FoundPW
