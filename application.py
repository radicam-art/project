import os
import sqlite3
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import pandas as pd

from loginReq import apology, login_required

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///hardware.db")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)

        # check confirmation
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation is NOT right", 400)

        names = db.execute("SELECT username FROM users")
        for row in range(len(names)):
            if request.form.get("username") == names[row]["username"]:
                return apology("This username is already used", 400)

        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)
        return redirect("/login")

    else:
        return render_template("register.html")

@app.route("/passcng", methods=["GET", "POST"])
@login_required
def passCng():
    if request.method == "POST":
        password = generate_password_hash(request.form.get("password"))
        afterPass = generate_password_hash(request.form.get("afterPass"))

        rows = db.execute("SELECT * FROM users WHERE id=:id", id=session["user_id"])

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid password", 400)

        if session["user_id"] == rows[0]["id"]:
            db.execute("UPDATE users SET hash=:hash WHERE id=:id", hash=afterPass, id=session["user_id"])
        return redirect("/")
    else:
        return render_template("passcng.html")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/")
@login_required
def route():
    """route page"""


    userName = db.execute("SELECT username FROM users WHERE id=:id", id = session["user_id"])
    name = userName[session["user_id"] - 1]["username"]

    return render_template("main.html", userName = name)

@app.route("/cpuData")
@login_required
def cpuData():
    """Show cpu-data"""
    db.execute("DELETE FROM cpuData")
    df = pd.read_csv("logFiles/cpuData.csv")
    dbname = 'hardware.db'

    df.columns = ['time', 'data']

    conn = sqlite3.connect(dbname)
    cur = conn.cursor()
    df.to_sql('cpuData', conn, if_exists='replace')

    cur.close()
    conn.close()

    cpuData = db.execute("SELECT time, data FROM cpuData")

    return render_template("cpuData.html", cpuData = cpuData)

@app.route("/gpuData")
@login_required
def gpuData():
    """Show gpu-data"""
    db.execute("DELETE FROM gpuData")
    df = pd.read_csv("logFiles/gpuData.log")
    dbname = 'hardware.db'

    df.columns = ['time', 'name', 'utilizationGpu', 'utilizationMem', 'memUsed', 'memFree']

    conn = sqlite3.connect(dbname)
    cur = conn.cursor()
    df.to_sql('gpuData', conn, if_exists='replace')

    cur.close()
    conn.close()

    gpuData = db.execute("SELECT time, name, utilizationGpu, utilizationMem, memUsed, memFree FROM gpuData")

    return render_template("gpuData.html", gpuData = gpuData)

@app.route("/memData")
@login_required
def memData():
    """Show mem-data"""
    db.execute("DELETE FROM memData")
    df = pd.read_csv("logFiles/memData.csv")
    dbname = 'hardware.db'

    df.columns = ['time', 'data']

    conn = sqlite3.connect(dbname)
    cur = conn.cursor()
    df.to_sql('memData', conn, if_exists='replace')

    cur.close()
    conn.close()

    memData = db.execute("SELECT time, data FROM memData")

    return render_template("memData.html", memData = memData)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)