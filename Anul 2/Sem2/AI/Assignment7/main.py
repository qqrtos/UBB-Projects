import traceback
from warnings import warn
from torch import load as torch_load, as_tensor

from create_db import TrainingDatasetFactory
from conf import get_ann
from training import Trainer
import matplotlib.pyplot as plt


def create_training_dataset(file_name, count=2000):
    if count:
        count = int(count)
    dataset = TrainingDatasetFactory(count)
    dataset.compute()
    dataset.save(file_name)


def graph_validation(differences_array):
    plt.xlabel('x - axis')
    plt.ylabel('difference value')
    differences_array = [float(e) for e in differences_array]
    plt.scatter(range(len(differences_array)), differences_array, s=0.2)
    plt.title('Difference rate in {} points'.format(len(differences_array)))
    plt.show()


def validate(model_name, file_name):
    ann = get_ann()
    ann.load_state_dict(torch_load(model_name))
    ann.eval()
    difference_list = []
    dataset = torch_load(file_name)
    for index in range(len(dataset)):
        x1, x2 = dataset.points[index]
        x = as_tensor([x1, x2])
        y = ann(x)
        result = dataset.results[index]
        difference_list.append(abs(result - y))
    graph_validation(difference_list)


def show(file_name):
    dataset = torch_load(file_name)
    print(str(dataset))


def train(file_name, net_file=None):
    trainer = Trainer(file_name, net_file)
    trainer.train()
    file_name = input("Do you want to save the model? Specify file name if so, or leave blank otherwise: ")
    if len(file_name) > 0:
        trainer.save(file_name)


def run(file_name, x1, x2):
    ann = get_ann()
    ann.load_state_dict(torch_load(file_name))
    ann.eval()
    x1 = float(x1)
    x2 = float(x2)
    x = as_tensor([x1, x2])
    print("f({:.3f}, {:.3f}) = {}".format(x1, x2, ann(x).tolist()))


def show_commands(commands):
    for command in commands:
        print(command)


def run_command(arguments, commands):
    command = arguments[0]
    if commands[command] is None:
        raise Exception("The command does not exist!")
    else:
        commands[command][0](*commands[command][1:], *arguments[1:])

def display_menu():
    print("1. Dataset: ")
    print("2. Train:")
    print("3. Run")
    print("0. Exit")

def menu():

    while True:
        display_menu()
        choose = int(input("Pick a nr: "))
        if choose == 1:
            fileName = input("File Name: ")
            create_training_dataset(fileName)
        elif choose == 2:
            dataSet = input("Data Set File: ")
            train(dataSet)
        elif choose == 3:
            file = input("Net File Name: ")
            x = input("X: ")
            y = input("Y: ")
            run(file, x, y)
        elif choose == 0:
            return


def command_application():
    commands = dict()
    commands["help"] = [show_commands, commands]
    commands["dataset"] = [create_training_dataset]
    commands["train"] = [train]
    commands["run"] = [run]
    commands["show"] = [show]
    commands["validate"] = [validate]
    while True:
        try:
            command = input()
            arguments = command.split(' ')
            run_command(arguments, commands)
        except Exception as E:
            warn(str(E) + traceback.format_exc())


if __name__ == "__main__":
    menu()
