problems = input()

print(len([i for i in map(int, input().strip().split()) if i < 0]))
