from collections import defaultdict

ZONES = 2
SHELVES = 4
SECTIONS = 18
LEVELS = 5
MAX_PER_CELL = 10
TOTAL_CAPACITY = 7200

class Cell:
    def __init__(self):
        self.product = ""
        self.quantity = 0

warehouse = defaultdict(Cell)

def init():
    for z in range(ZONES):
        zone = chr(ord('A') + z)
        for s in range(1, SHELVES + 1):
            for sec in range(1, SECTIONS + 1):
                for l in range(1, LEVELS + 1):
                    addr = f"{zone}{s}{sec:02d}{l}"
                    warehouse[addr] = Cell()

def valid_address(address):
    if len(address) not in [4, 5]:
        return False
    if address[0] not in ['A', 'B']:
        return False
    try:
        shelf = int(address[1])
        if not (1 <= shelf <= 4):
            return False

        if len(address) == 4:
            section = int(address[2])
            level = int(address[3])
        else:
            section = int(address[2:4])
            level = int(address[4])

        return 1 <= section <= 18 and 1 <= level <= 5
    except ValueError:
        return False

def add(name, qty, addr):
    if not valid_address(addr):
        print("Такой ячейки не может быть!")
        return
    cell = warehouse[addr]
    if cell.product and cell.product != name:
        print("В ячейке другой товар!")
    elif cell.quantity + qty > MAX_PER_CELL:
        print("В ячейке нет столько места!")
    else:
        cell.product = name
        cell.quantity += qty
        print("Добавлено", qty, "шт", name, "в", addr)

def remove(name, qty, addr):
    if not valid_address(addr):
        print("Такой ячейки не может быть!")
        return
    cell = warehouse[addr]
    if cell.product and cell.product != name:
        print("В ячейке другой товар!")
    elif cell.product != name or cell.quantity < qty:
        print("В ячейке нет столько товара!")
    else:
        cell.quantity -= qty
        if cell.quantity == 0:
            cell.product = ""
        print("Удалено", qty, "шт", name, "из", addr)

def info():
    used = 0
    zone_used = [0 for _ in range(ZONES)]
    for addr, cell in warehouse.items():
        used += cell.quantity
        if cell.quantity:
            zone_used[ord(addr[0]) - ord('A')] += cell.quantity

    print("Склад:", round(used / TOTAL_CAPACITY * 100, 2), "%")
    for i in range(ZONES):
        capacity_zone = SHELVES * SECTIONS * LEVELS * MAX_PER_CELL
        print("Зона " + chr(ord('A') + i) + ":", round(zone_used[i] / capacity_zone * 100, 2), "%")

    for addr, cell in warehouse.items():
        if cell.quantity:
            print(addr, ":", cell.product, "-", cell.quantity)



init()
while True:
    try:
        parts = input().strip().split()
    except EOFError:
        break
    if not parts:
        continue
    cmd = parts[0].upper()
    if cmd == "EXIT":
        break
    elif cmd == "ADD" and len(parts) == 4:
        name, qty, addr = parts[1], int(parts[2]), parts[3]
        add(name, qty, addr)
    elif cmd == "REMOVE" and len(parts) == 4:
        name, qty, addr = parts[1], int(parts[2]), parts[3]
        remove(name, qty, addr)
    elif cmd == "INFO":
        info()
    else:
        print("Неизвестная команда.")

