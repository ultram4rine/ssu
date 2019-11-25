import datetime
import csv
from classes import Route, Driver, Work
from csv_work import read_routes_from_csv, read_drivers_from_csv, read_works_from_csv, write_routes_to_csv, write_drivers_to_csv, write_works_to_csv


routes = read_routes_from_csv('csv/routes.csv')

for route in routes:
    route.display_info()

drivers = read_drivers_from_csv('csv/drivers.csv')

for driver in drivers:
    driver.display_info()

works = read_works_from_csv(
    'csv/works.csv', 'csv/routes.csv', 'csv/drivers.csv')

for work in works:
    work.display_info()

write_routes_to_csv(routes, 'csv/out/routes.csv')

write_drivers_to_csv(drivers, 'csv/out/drivers.csv')

write_works_to_csv(works, 'csv/out/works.csv')
