# Concatenate 2 lists.
# concat(l1…ln, k1…km)
# 	* {}	 if n=0 and m=0
# 	* {l1} U concat([l2…ln], {})		if n>0 and m=0
# 	* {k1} U concat({}, [k2…km])		if n=0 and m>0
# 	* {l1} U {k1} U concat([l2…ln], [k2…km])		if n>0 and m>0
import lista


def concat(list1, list2):
    if list1.urm is not None:
        concat(list1.urm, list2)
    else:
        list1.urm = list2

print('Creare lista 1:')
list1 = lista.creareLista()
print('Creare lista 2:')
list2 = lista.creareLista()
concat(list1.prim, list2.prim)
lista.tipar(list1)
