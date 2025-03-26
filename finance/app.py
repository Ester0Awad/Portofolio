import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user's stocks and shares
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP By symbol HAVING total_shares > 0 ",
        user_id=session["user_id"],
    )

    # Get user's cash balance
    cash = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )[0]["cash"]

    # Initialize variables for total values
    total_value = cash
    grand_total = cash

    # Iterate over stocks and add `price` and `total value`
    for stock in stocks:
        # Use the `lookup` function provided to get the current price of that stock
        quote = lookup(stock["symbol"])
        # stock(["price"]) = quote["price"]
        stock["price"] = quote["price"]
        stock["value"] = quote["price"] * stock["total_shares"]
        total_value += stock["value"]
        grand_total += stock["value"]

    return render_template(
        "index.html",
        stocks=stocks,
        cash=cash,
        total_value=total_value,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Get the symbol that the user has inputted in uppercase letters
        symbol = request.form.get("symbol").upper()

        # Get the shares that the user has inputted
        shares = request.form.get("shares")

        # Ensure symbol's name is submitted (a.k.a field is not blank)
        if not symbol:
            return apology("Must provide a symbol", 400)

        # Make sure that `shares` is a positive number
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Invalid number", 400)

        # Use the `lookup` function provided to get the current price of that stock
        quote = lookup(symbol)
        if quote is None:
            return apology("Symbol not Found", 400)

        price = quote["price"]
        # Calculate the total cost

        # print(type(price))
        # print(type(shares))

        #       total_cost = float(price) * int(shares)

        # `SELECT` how much cash the user currently has in "users" table
        cash = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["cash"]

        # Calculate the total cost
        total_cost = price * int(shares)

        # Compare user's cash to the total cost of the stock to see if the user can afford it.
        if cash < total_cost:
            return apology("You don't have enough cash", 400)

        # Update user's cash in database
        db.execute(
            "UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
            total_cost=total_cost,
            user_id=session["user_id"],
        )

        # Insert a new row into `transactions` table, to purchase a stock (a.k.a Add the purchase to the history table)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
            user_id=session["user_id"],
            symbol=symbol,
            shares=shares,
            price=price,
        )

        # After completion, redirect the user to the home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # 3   transactions = db.execute("SELECT  symbol, shares, price, timestamp FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC",
        user_id=session["user_id"],
    )

    # Render history page with transactions
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Get the symbol that the user has inputted
        symbol = request.form.get("symbol")

        # Use the `lookup` function provided to get the current price of that stock
        quote = lookup(symbol)

        if not quote:
            return apology("Invalid symbol", 400)

        return render_template("quote.html", quote=quote)

    # User reached route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted (a.k.a username field is not blank)
        if not request.form.get("username"):
            return apology("Must provide username", 400)

        # Ensure password was submitted (a.k.a password field is not blank)
        elif not request.form.get("password"):
            return apology("Must provide password", 400)

        # Ensure confirmation was submitted (a.k.a confirmation field is not blank)
        elif not request.form.get("confirmation"):
            return apology("Must confirm password", 400)

        # Ensure that password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password and Confirmation do not match", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username is unique (a.k.a the new username doesn't exisit in the database)
        if len(rows) != 0:
            return apology("Username is already exists", 400)

        # Insert new user into database & hashed password into the data base if don't exisist in the database
        hashed_password = generate_password_hash(request.form.get("password"))
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?);",
            request.form.get("username"),
            hashed_password,
        )

        # Query database for newly inserted user
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect the user to the homepage
        return redirect("/")

        # Insert that new username

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get user's stocks and shares
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP By symbol HAVING total_shares > 0 ",
        user_id=session["user_id"],
    )
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Get the symbol that the user has inputted
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("Must provide symbol")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Must provide a positive integer number of shares")
        else:
            shares = int(shares)

        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("Not enough shares")
                else:
                    # Get quote
                    quote = lookup(symbol)
                    if quote is None:
                        return apology("Symbol not found")
                    price = quote["price"]
                    total_sale = shares * price

                    # Update `users` table
                    db.execute(
                        "UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                        total_sale=total_sale,
                        user_id=session["user_id"],
                    )

                    # Add the sale to the history table
                    db.execute(
                        "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                        user_id=session["user_id"],
                        symbol=symbol,
                        shares=-shares,
                        price=price,
                    )

                    # Redirect the user to the homepage
                    return redirect("/")

        return apology("Symbol not found")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", stocks=stocks)
