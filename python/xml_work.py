from xml.dom import minidom
import xml.etree.ElementTree as ET
from classes import Route, Driver, Work


def read_routes_from_xml(filename):
    doc = minidom.parse(filename)

    elements = doc.getElementsByTagName('route')

    routes = []

    for e in elements:
        route = Route(
            id=e.attributes['id'].value,
            name=e.childNodes[1].firstChild.data,
            distance=e.childNodes[3].firstChild.data,
            days=e.childNodes[5].firstChild.data,
            payment=e.childNodes[7].firstChild.data,
        )

        routes.append(route)

    return routes


def read_drivers_from_xml(filename):
    doc = minidom.parse(filename)

    elements = doc.getElementsByTagName('driver')

    drivers = []

    for e in elements:
        driver = Driver(
            id=e.attributes['id'].value,
            surname=e.childNodes[1].firstChild.data,
            name=e.childNodes[3].firstChild.data,
            patronymic=e.childNodes[5].firstChild.data,
            exp=e.childNodes[7].firstChild.data
        )

        drivers.append(driver)

    return drivers


def read_works_from_xml(filename):
    doc = minidom.parse(filename)

    elements = doc.getElementsByTagName('work')

    works = []

    for e in elements:
        route = doc.getElementsByTagName('route')[0]
        driver = doc.getElementsByTagName('driver')[0]

        work = Work(
            id=e.attributes['id'].value,
            route=Route(route.attributes['id'].value,
                        route.childNodes[1].firstChild.data, route.childNodes[3].firstChild.data, route.childNodes[5].firstChild.data, route.childNodes[7].firstChild.data),
            driver=Driver(driver.attributes['id'].value, driver.childNodes[1].firstChild.data,
                          driver.childNodes[3].firstChild.data, driver.childNodes[5].firstChild.data, driver.childNodes[7].firstChild.data),
            date_departure=e.childNodes[5].firstChild.data,
            date_return=e.childNodes[7].firstChild.data,
            premium=e.childNodes[9].firstChild.data
        )

        works.append(work)

    return works


def write_route_to_xml(routes, filename):
    data = ET.Element('data')

    routesEL = ET.SubElement(data, 'routes')

    for r in routes:
        route = ET.SubElement(routesEL, 'route')

        name = ET.SubElement(route, 'name')
        name.text = r.name

        distance = ET.SubElement(route, 'distance')
        distance.text = r.distance

        days = ET.SubElement(route, 'days')
        days.text = r.days

        payment = ET.SubElement(route, 'payment')
        payment.text = r.payment

    mydata = ET.tostring(data, encoding="unicode")
    file = open(filename, "w")
    file.write(mydata)


def write_driver_to_xml(drivers, filename):
    data = ET.Element('data')

    driversEL = ET.SubElement(data, 'drivers')

    for d in drivers:
        driver = ET.SubElement(driversEL, 'route')

        surname = ET.SubElement(driver, 'surname')
        surname.text = d.surname

        name = ET.SubElement(driver, 'name')
        name.text = d.name

        patronymic = ET.SubElement(driver, 'patronymic')
        patronymic.text = d.patronymic

        exp = ET.SubElement(driver, 'exp')
        exp.text = d.exp

    mydata = ET.tostring(data, encoding="unicode")
    file = open(filename, "w")
    file.write(mydata)
