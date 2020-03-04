b,l,d,books = None, None, None, None
libraries = {}
with open('c_incunabula.txt') as f:
    b, l, d = list(map(int, f.readline().split()))
    books = list(map(int, f.readline().split()))
    for i in range(l):
        n, sign, scan = list(map(int, f.readline().split()))
        l_books = list(map(int, f.readline().split()))
        libraries[i] = (n, sign, scan, l_books)
    
#print(b, l, d, books)
#print(libraries)


# Let parameter = totalscore * scanperday / sign up time^3
parameters = {}
for lib in libraries:
    totalscore = 0
    for b in libraries[lib][3]:
        totalscore += books[b]
    parameters[lib] = totalscore * libraries[lib][2] / ((libraries[lib][1])) ** 3

#print('Parameters:', parameters)

#Sort the parameter dictionary in ascending order
items = parameters.items()
sorted_items = sorted(items, key=lambda x: x[1], reverse=True)
#print('Sorted Parameters:', sorted_items)

#Schedule libraries based on parameters

with open('c_incunabula_op_old.txt', 'w') as f:
    f.write(str(len(sorted_items)) + '\n')
    for library in sorted_items:
        lib = library[0]
        #We need to diplay library id, number of books to send and which books to send
        #Brute force: Send everything. System will automatically reject books that cross d
        f.write(str(lib) + ' ' +   str(libraries[lib][0]) + '\n')
        for i in sorted(libraries[lib][3], reverse=True):
            f.write(str(i) + ' ')
        f.write('\n')