# Insert an element at the end of a list.
# insert([l1...ln], elem)
# * {elem}		if n=0
# * {l1} U insert([l2...ln], elem)		otherwise
import lista


def insert(mylist, elem):
    if mylist.urm is None:
        mylist.urm = lista.Nod(elem)
    else:
        insert(mylist.urm, elem)
    return mylist


print('Creare lista:')
mylist = lista.creareLista()
insert(mylist.prim, 5)
lista.tipar(mylist)
