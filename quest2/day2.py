ranges = [
    (11,22),
    (95,115),
    (998,1012),
    (1188511880,1188511890),
    (222220,222224),
    (1698522,1698528),
    (446443,446449),
    (38593856,38593862)
]

invalidNumberValue = 0

for start, end in ranges:
    for n in range(start, end +1):
        s = str(n)
        if len(s) %2 == 0:
            half = len(s) // 2 
            if s[:half] == s[half:]:
                print(n)
                invalidNumberValue = invalidNumberValue + n

print(invalidNumberValue)