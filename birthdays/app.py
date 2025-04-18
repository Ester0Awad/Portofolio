import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database

        # Access from data
        name = request.form.get("name")
        if not name:
            return redirect("/")

        month = request.form.get("month")
        if not month:
            return redirect("/")

        try:
            month = int(month)
        except ValueError:
            return redirect("/")

        if month < 0 or month > 12:
            return redirect("/")

        day = request.form.get("day")
        if not day:
            return redirect("/")

        try:
            day = int(day)
        except ValueError:
            return redirect("/")

        if day < 0 or day > 31:
            return redirect("/")

        # Insert data into database
        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);",
            name,
            month,
            day,
        )

        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html

        # Pass the data in the Python variable `birthdays`, the second one, to the `index.html` file,
        # and in that file, refer to this data as `birthdays`
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render birthdays page
        return render_template("index.html", birthdays=birthdays)
