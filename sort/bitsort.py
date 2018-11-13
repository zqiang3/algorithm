
MAX = 10000000

arr = [0] * MAX

f = open("numbers.txt", 'r')
for line in f:
    num = int(line)
    arr[num] = 1

f.close()

outfile = open("result2", 'w')
for i, value in enumerate(arr):
    if value == 1:
        outfile.write(str(i))
        outfile.write('\n')

outfile.close()
        
