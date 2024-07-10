import init_db
import database
import user_input
import gui
from categories import Category


def test_operations():
    # Initialize and clear your database for a clean test environment
    init_db.create_database()
    database.clear_database()


    # Insert sample transactions
    database.insert_transaction(category=Category.GROCERIES, amount=-100.00, description="Electric bill", date="2024-03-20")
    database.insert_transaction(category=Category.SALARY, amount=2000.00, description="Monthly salary", date="2024-03-25")

    # Insert user input sample transactions via console
    #user_input.add_transaction()

    # Fetch and print all transactions
    transactions = database.get_all_transactions()
    database.print_user_friendly_transactions(transactions)

if __name__ == '__main__':
    test_operations()

