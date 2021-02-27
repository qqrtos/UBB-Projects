#procedural programming

def initialize():
     grade=5
     print("Enter the corresponding number for the options below:")
     print("1. Add a student")
     print("2. Delete a student")
     print("3. Show all students")
     print("4. Show students with a grade > than "+str(grade))
     print("5. Exit the application\n\n")


def createStudent(sid, sname = "n/a", sgrade = None): #sgrade is a default parameter (it has a default value if not specified)
     return {"id":sid,"name":sname,"grade":sgrade}
def showStudents(stud):
     print(stud)

def set_stud_id(student,sid):
     student["id"]=sid
def set_stud_name(student,sname):
     student["name"]=sname
def set_stud_grade(student,sgrade):
     student["grade"]=sgrade
def get_stud_id(student):
     return student["id"]
def get_stud_name(student):
     return student["name"]
def get_stud_grade(student):
     return student["grade"]



def runProgram():
     initialize()
     students=[]
     students.append(createStudent(1,"Carnat",2))
     students.append(createStudent(2,"Balama",6))
     while True:
          choice = input(">")
          if choice is "3":
               showStudents(students)
          elif choice is "5":
               return


runProgram()
