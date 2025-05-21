import random
import sys

class Visitor:
    def __init__(self, ticket, duration):
        self.ticket = ticket
        self.duration = duration

def generate_ticket(ticket_pool, ticket_index):
    if ticket_index[0] >= len(ticket_pool):
        return None
    ticket = "T" + str(ticket_pool[ticket_index[0]])
    ticket_index[0] += 1
    return ticket

def backtrack(idx, times, curr_dist, visitors, window_count, best_result):
    if idx == len(visitors):
        current_makespan = max(times)
        if current_makespan < best_result['makespan']:
            best_result['makespan'] = current_makespan
            best_result['distribution'] = [list(window) for window in curr_dist]
        return

    v = visitors[idx]
    for i in range(window_count):
        times[i] += v.duration
        curr_dist[i].append(v)

        if max(times) < best_result['makespan']:
            backtrack(idx + 1, times, curr_dist, visitors, window_count, best_result)

        times[i] -= v.duration
        curr_dist[i].pop()


print("Введите количество окон: ", end="")
n = int(input())

ticket_pool = list(range(100, 1000))
random.shuffle(ticket_pool)
ticket_index = [0]

visitors = []
while True:
    try:
        parts = input().strip().split()
    except EOFError:
        break
    if not parts:
        continue
    cmd = parts[0].upper()
    if cmd == "DISTRIBUTE":
        break
    if cmd == "ENQUEUE" and len(parts) == 2:
        dur = int(parts[1])
        ticket = generate_ticket(ticket_pool, ticket_index)
        if ticket is None:
            print("Билеты закончились.")
            break
        print(ticket)
        visitors.append(Visitor(ticket, dur))

times = [0] * n
current_distribution = [[] for _ in range(n)]
best_result = {'makespan': sys.maxsize, 'distribution': []}

backtrack(0, times, current_distribution, visitors, n, best_result)

for i in range(n):
    total = sum(v.duration for v in best_result['distribution'][i])
    print("Окно " + str(i + 1) + " (" + str(total) + " минут): ", end="")
    print(", ".join(v.ticket for v in best_result['distribution'][i]))
