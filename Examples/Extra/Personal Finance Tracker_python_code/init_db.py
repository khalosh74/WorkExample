"""
Overview
This script, typically named something like init_db.py,
 is designed to initialize the SQLite database for a
 Personal Finance Tracker application. It ensures the
 necessary tables for storing categories and transactions
 are created. This setup script needs to be run once before
 the application is used for the first time, or when setting
  up the application on a new system.
"""
import sqlite3


def create_database():
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('finance_tracker.db')
    c = conn.cursor()

    # Create Categories table
    c.execute('''CREATE TABLE IF NOT EXISTS Categories (
                  id INTEGER PRIMARY KEY,
                  name TEXT NOT NULL
                )''')

    # Create Transactions table
    c.execute('''CREATE TABLE IF NOT EXISTS Transactions (
                  id INTEGER PRIMARY KEY,
                  category_id INTEGER,
                  amount REAL NOT NULL,
                  description TEXT,
                  date DATE NOT NULL,
                  FOREIGN KEY (category_id) REFERENCES Categories(id)
                )''')

    # Save (commit) the changes and close the connection
    conn.commit()
    conn.close()


if __name__ == '__main__':
    create_database()