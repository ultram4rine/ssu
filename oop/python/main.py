from classes import Route, Driver, Work

from csv_work import read_routes_from_csv, read_drivers_from_csv, read_works_from_csv, write_routes_to_csv, write_drivers_to_csv, write_works_to_csv

from xml_work import read_routes_from_xml, read_drivers_from_xml, read_works_from_xml, write_routes_to_xml, write_drivers_to_xml, write_works_to_xml

from sqlite_work import read_routes_from_sqlite, read_drivers_from_sqlite, read_works_from_sqlite, write_routes_to_sqlite, write_drivers_to_sqlite, write_works_to_sqlite

routesCSV = read_routes_from_csv('csv/routes.csv')
for route in routesCSV:
    route.display_info()

driversCSV = read_drivers_from_csv('csv/drivers.csv')
for driver in driversCSV:
    driver.display_info()

worksCSV = read_works_from_csv(
    'csv/works.csv', 'csv/routes.csv', 'csv/drivers.csv')
for work in worksCSV:
    work.display_info()

write_routes_to_csv(routesCSV, 'csv/out/routes.csv')

write_drivers_to_csv(driversCSV, 'csv/out/drivers.csv')

write_works_to_csv(worksCSV, 'csv/out/works.csv')

routesXML = read_routes_from_xml('xml/routes.xml')
for route in routesXML:
    route.display_info()

driversXML = read_drivers_from_xml('xml/drivers.xml')
for driver in driversXML:
    driver.display_info()

worksXML = read_works_from_xml('xml/works.xml')
for work in worksXML:
    work.display_info()

write_routes_to_xml(routesXML, 'xml/out/routes.xml')

write_drivers_to_xml(driversXML, 'xml/out/drivers.xml')

write_works_to_xml(worksXML, 'xml/out/works.xml')

write_routes_to_sqlite(routesXML)

write_drivers_to_sqlite(driversXML)

write_works_to_sqlite(worksXML)

routesSQL = read_routes_from_sqlite()
for route in routesSQL:
    route.display_info()

driversSQL = read_drivers_from_sqlite()
for driver in driversSQL:
    driver.display_info()

worksSQL = read_works_from_sqlite()
for work in worksSQL:
    work.display_info()
