class Route:
    def __init__(self, id, name, distance, days, payment):
        self.id = id
        self.name = name
        self.distance = distance
        self.days = days
        self.payment = payment

    def __iter__(self):
        return iter([self.id, self.name, self.distance, self.days, self.payment])

    def display_info(self):
        print("Маршрут", self.name, "\nДистанция:", self.distance, "км",
              "\nВ днях:", self.days, "дней", "\nОплата:", self.payment, "рублей\n")


class Driver:
    def __init__(self, id, surname, name, patronymic, exp):
        self.id = id
        self.surname = surname
        self.name = name
        self.patronymic = patronymic
        self.exp = exp

    def __iter__(self):
        return iter([self.id, self.surname, self.name, self.patronymic, self.exp])

    def display_info(self):
        print("Водитель:", self.surname, self.name,
              self.patronymic, "\nСтаж:", self.exp, "лет\n")


class Work:
    def __init__(self, id, route, driver, date_departure, date_return, premium):
        self.id = id
        self.route = route
        self.driver = driver
        self.date_departure = date_departure
        self.date_return = date_return
        self.premium = premium

    def __iter__(self):
        return iter([self.id, self.route.id, self.driver.id, self.date_departure, self.date_return, self.premium])

    def display_info(self):
        print("Проделанная работа:\n")
        self.route.display_info()
        print()
        self.driver.display_info()
        print("\nДата отправки:", self.date_departure, "\nДата возвращения:",
              self.date_return, "\nПремия:", self.premium, "рублей\n")
