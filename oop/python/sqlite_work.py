import sqlite3
from classes import Route, Driver, Work


def read_routes_from_sqlite():
    conn = sqlite3.connect('sqlite/sqlite.db')
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM routes")

    routes = []
    for r in cursor.fetchall():
        routes.append(Route(r[0], r[1], r[2], r[3], r[4]))

    return routes


def read_drivers_from_sqlite():
    conn = sqlite3.connect('sqlite/sqlite.db')
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM drivers")

    drivers = []
    for r in cursor.fetchall():
        drivers.append(Route(r[0], r[1], r[2], r[3], r[4]))

    return drivers


def read_works_from_sqlite():
    conn = sqlite3.connect('sqlite/sqlite.db')
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM works")

    works = []
    for r in cursor.fetchall():
        route = cursor.execute(
            "SELECT * FROM routes WHERE id = ?", r[1]).fetchone()
        driver = cursor.execute(
            "SELECT * FROM drivers WHERE id = ?", r[2]).fetchone()
        works.append(Work(r[0], Route(route[0], route[1], route[2], route[3], route[4]), Driver(
            driver[0], driver[1], driver[2], driver[3], driver[4]), r[3], r[4], r[5]))

    return works


def write_routes_to_sqlite(routes):
    conn = sqlite3.connect('sqlite/sqlite.db')
    cursor = conn.cursor()

    cursor.execute("DROP TABLE IF EXISTS routes")
    conn.commit()

    cursor.execute(
        """CREATE TABLE IF NOT EXISTS routes(id TEXT, name TEXT, distance TEXT, days TEXT, payment TEXT)""")
    conn.commit()

    for r in routes:
        r_tuple = (r.id, r.name, r.distance, r.days, r.payment)
        cursor.execute("INSERT INTO routes VALUES (?, ?, ?, ?, ?)", r_tuple)
    conn.commit()

    cursor.close()
    conn.close()


def write_drivers_to_sqlite(drivers):
    conn = sqlite3.connect('sqlite/sqlite.db')
    cursor = conn.cursor()

    cursor.execute("DROP TABLE IF EXISTS drivers")
    conn.commit()

    cursor.execute(
        """CREATE TABLE IF NOT EXISTS drivers(id TEXT, surname TEXT, name TEXT, patronymic TEXT, exp TEXT)""")
    conn.commit()

    for d in drivers:
        d_tuple = (d.id, d.surname, d.name, d.patronymic, d.exp)
        cursor.execute("INSERT INTO drivers VALUES (?, ?, ?, ?, ?)", d_tuple)
    conn.commit()

    cursor.close()
    conn.close()


def write_works_to_sqlite(works):
    conn = sqlite3.connect('sqlite/sqlite.db')
    cursor = conn.cursor()

    cursor.execute("DROP TABLE IF EXISTS works")
    conn.commit()

    cursor.execute(
        """CREATE TABLE IF NOT EXISTS works(id TEXT, route TEXT, driver TEXT, date_departure TEXT, date_return TEXT, premium TEXT)""")
    conn.commit()

    for w in works:
        w_tuple = (w.id, w.route.id, w.driver.id,
                   w.date_departure, w.date_return, w.premium)
        cursor.execute("INSERT INTO works VALUES (?, ?, ?, ?, ?, ?)", w_tuple)
    conn.commit()

    cursor.close()
    conn.close()
