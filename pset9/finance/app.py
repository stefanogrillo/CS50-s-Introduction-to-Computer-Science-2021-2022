import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():

    if request.method == "GET":
        # We just need the GET method, which is set as default

        user_id = session["user_id"]

        # Create values from DB into a Table with fields of Symbol, Name, Shares, Time and add a line for Tot User Cash
        stocks = db.execute("SELECT symbol, name, SUM(shares) as totShares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        total = cash

        for stock in stocks:
            total += stock["price"] * stock["totShares"]

        return render_template("index.html", stocks=stocks, cash=cash, usd=usd, total=total)
    else:
        symbol = request.form.get("symbol")

        
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    # At this point we create a new table in the database, table called: Transactions
    # Which includes columns: id, user_id, name, shares, price, type, symbol, time
    # (CREATE TABLE transactions (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, name TEXT NOT NULL, 
    #       shares INTEGER NOT NULL, price NUMERIC NOT NULL, type TEXT NOT NULL, symbol TEXT NOT NULL, time TIMESTAMP DEFAULT CURRENT_TIMESTAMP, 
    #       FOREIGN KEY(user_id) REFERENCES users(id) );

    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()
        item = lookup(symbol)

        if not symbol:
            return apology("Insert the Symbol of a Company")
        elif not item:
            return apology("This was an Invalid Symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares Must Be Integer")

        if shares <= 0:
            return apology("Shares Must Be Positive")

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        item_name = item["name"]
        item_price = item["price"]
        total_price = item_price * shares

        if cash < total_price:
            return apology("You Can't Afford It Yet")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)
            db.execute("INSERT INTO transactions(user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                user_id, item_name, shares, item_price, "buy", symbol)

        return redirect('/')


@app.route("/history")
@login_required
def history():

    user_id = session["user_id"]
    symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    transactions = db.execute("SELECT type, symbol, price, shares, time FROM transactions WHERE user_id = ?",
                        user_id)

    return render_template("history.html", transactions=transactions, usd=usd, symbols=symbols)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash("Welcome Back!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

