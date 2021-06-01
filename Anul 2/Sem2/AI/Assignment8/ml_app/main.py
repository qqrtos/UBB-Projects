import traceback
from warnings import warn
from torch import load as torch_load, as_tensor
from ml_app.create_db import ImageDataset, ImagesPathFactory
from ml_app.conf import get_ann
from ml_app.network_model import Network
from ml_app.testing import Tester
from ml_app.training import Trainer

from ml_app.task1 import test_image
import json


class CommandApplication:
    def __init__(self):
        self.commands = dict()
        self.commands["help"] = [self.show_commands]
        self.commands["run"] = [self.run]
        self.model = None
        self.training_dataset = None
        self.test_dataset = None

    def run_config(self):
        with open("config.json") as config:
            config = json.loads(config.read())
            paths = ImagesPathFactory()
            for dataset_path in config["datasets"]:
                paths.load_directory(dataset_path[0], dataset_path[1])
            dataset = ImageDataset(paths.dataset)
            dataset.shuffle()
            self.training_dataset, self.test_dataset = dataset.split(config["split_ratio"])
            self.training_dataset.shuffle()
            self.test_dataset.shuffle()
            self.model = Network()
            #self.model.load_state_dict(torch_load("latest_best_model"))
            self.model.eval()
            tester = Tester(self.test_dataset, self.model)
            trainer = Trainer(self.training_dataset, self.model, tester)
            trainer.train()

            print("Testing accuracy:", tester.test())

    def run(self, file_name, x1=None, x2=None):
        if file_name == "config":
            self.run_config()
            return
        ann = get_ann()
        ann.load_state_dict(torch_load(file_name))
        ann.eval()
        x1 = float(x1)
        x2 = float(x2)
        x = as_tensor([x1, x2])
        print("f({:.3f}, {:.3f}) = {}".format(x1, x2, ann(x).tolist()))

    def show_commands(self):
        for command in self.commands:
            print(command)

    def run_command(self, arguments):
        command = arguments[0]
        if self.commands[command] is None:
            raise Exception("The command does not exist!")
        else:
            self.commands[command][0](*self.commands[command][1:], *arguments[1:]) # noqa

    def command_application(self):
        while True:
            try:
                command = input()
                arguments = command.split(' ')
                self.run_command(arguments)
            except Exception as E:
                warn(str(E) + traceback.format_exc())


if __name__ == "__main__":
    test_image()
    app = CommandApplication()
    app.command_application()
