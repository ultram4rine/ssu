import csv
from classes import Route, Driver, Work


def read_routes_from_csv(filename):
    routes = []

    with open(filename, 'r') as f:
        rows = csv.reader(f)

        for row in rows:
            route = Route(
                id=row[0],
                name=row[1],
                distance=row[2],
                days=row[3],
                payment=row[4]
            )

            routes.append(route)

    return routes


def read_drivers_from_csv(filename):
    drivers = []

    with open(filename, 'r') as f:
        rows = csv.reader(f)

        for row in rows:
            driver = Driver(
                id=row[0],
                surname=row[1],
                name=row[2],
                patronymic=row[3],
                exp=row[4],
            )

            drivers.append(driver)

    return drivers


def read_works_from_csv(filename, routesfile, driversfile):
    works = []

    with open(filename, 'r') as f:
        rows = csv.reader(f)

        for row in rows:
            route = read_routes_from_csv(routesfile)[int(row[1])]
            driver = read_drivers_from_csv(driversfile)[int(row[2])]

            work = Work(
                id=row[0],
                route=route,
                driver=driver,
                date_departure=row[3],
                date_return=row[4],
                premium=row[5]
            )

            works.append(work)

    return works


def write_routes_to_csv(routes, filename):
    with open(filename, 'w') as f:
        writer = csv.writer(f, dialect='excel')

        for route in routes:
            writer.writerow(route)


def write_drivers_to_csv(drivers, filename):
    with open(filename, 'w') as f:
        writer = csv.writer(f, dialect='excel')

        for driver in drivers:
            writer.writerow(driver)


def write_works_to_csv(works, filename):
    with open(filename, 'w') as f:
        writer = csv.writer(f, dialect='excel')

        for work in works:
            writer.writerow(work)
