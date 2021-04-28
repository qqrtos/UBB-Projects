import pandas as pd
import numpy as np
import matplotlib.pyplot as plot
import matplotlib.patches as patch


class Record:
    def __init__(self, label, first_value, second_value):
        self.__label = label
        self.__first_value = first_value
        self.__second_value = second_value

    @property
    def label(self):
        return self.__label

    @property
    def first(self):
        return self.__first_value

    @property
    def second(self):
        return self.__second_value

    def distance_to(self, other):
        centroid = other.centroid
        return np.sqrt((self.first - centroid.first) ** 2 + (self.second - centroid.second) ** 2)


class Cluster:
    def __init__(self, centroid):
        self.__centroid = centroid
        self.__records = []
        self.__label = None  # THE LABEL IS DETERMINED BY THE PREDOMINANT LABEL IN THE CLUSTER

    @property
    def centroid(self):
        return self.__centroid

    @property
    def records(self):
        return self.__records[:]

    def update(self):  # UPDATES THE CENTROID OF THE CLUSTER ( MEDIA ARITMETICA A PUNCTELOR DIN CLUSTER)
        center_first = 0
        center_second = 0
        size = len(self.__records)
        for record in self.__records:
            center_first += record.first
            center_second += record.second
        center_first /= size
        center_second /= size
        self.__centroid = Record(None, center_first, center_second)

    def add(self, record):
        self.__records.append(record)

    def remove(self, record):
        self.__records.remove(record)

    @property
    def label(self):
        return self.__label

    def compute_label(self):  # PREIA CEL MAI INTALNIT LABEL SI IL PUNE CA SEF PESTE CLUSTER
        labels = {
            'A': 0,
            'B': 0,
            'C': 0,
            'D': 0
        }
        for record in self.__records:
            labels[record.label] += 1
        self.__label = max(labels.keys(), key=lambda label: labels[label])


def get_best_cluster(record, clusters):
    return min(clusters, key=lambda cluster: record.distance_to(cluster))


def iteration(clusters):  # MERGE PE TOATE POINTS SI VEDE CE CLUSTER E CEL MAI APROPIAT
    record_sets = [[cluster.records, cluster] for cluster in clusters]
    for record_set in record_sets:
        old_cluster: Cluster = record_set[1]
        for record in record_set[0]:
            new_cluster: Cluster = get_best_cluster(record, clusters)
            if old_cluster != new_cluster:
                old_cluster.remove(record)
                new_cluster.add(record)
    for cluster in clusters:
        cluster.update()
        cluster.compute_label()


# CAT DE ACCURATE II ( MERE SI VEDE CATE LABLE-URI O GHICIT) DIN FISIER IN RAPORT CU ALEA PE CARE LE-O PUS EL
def compute_accuracy_index(clusters):
    correct_count = 0
    total_count = 0
    for cluster in clusters:
        for record in cluster.records:
            total_count += 1
            if record.label == cluster.label:
                correct_count += 1
    if total_count == 0:
        return 0
    return correct_count / total_count


def compute_precision(clusters):  # COUNT DIN CLUSTER IN RAPORT CU CORRECT COUNT DINTR-UN CLUSTER(PRECIZIA)
    labels = {  # noqa
        'A': {'correct_count': 0, 'total_count': 0},
        'B': {'correct_count': 0, 'total_count': 0},
        'C': {'correct_count': 0, 'total_count': 0},
        'D': {'correct_count': 0, 'total_count': 0}
    }
    for cluster in clusters:
        for record in cluster.records:
            labels[cluster.label]['total_count'] += 1
            if record.label == cluster.label:
                labels[record.label]['correct_count'] += 1
    for label in labels:
        if labels[label]['total_count'] != 0:
            labels[label] = labels[label]['correct_count'] / labels[label]['total_count']
        else:
            labels[label] = 0
    return labels


def compute_rappel(clusters):  # TOTAL COUNT IN RAPORT CU CORRECT COUNT(PER CLUSTER)
    labels = {
        'A': {'correct_count': 0, 'total_count': 0},
        'B': {'correct_count': 0, 'total_count': 0},
        'C': {'correct_count': 0, 'total_count': 0},
        'D': {'correct_count': 0, 'total_count': 0}
    }
    for cluster in clusters:
        for record in cluster.records:
            labels[record.label]['total_count'] += 1
            if record.label == cluster.label:
                labels[record.label]['correct_count'] += 1
    for label in labels:
        if labels[label]['total_count'] != 0:
            labels[label] = labels[label]['correct_count'] / labels[label]['total_count']
        else:
            labels[label] = 0
    return labels


def compute_score(clusters):  # the score of a cluster
    score = {
        'A': 0,
        'B': 0,
        'C': 0,
        'D': 0
    }
    precision = compute_precision(clusters)
    rappel = compute_rappel(clusters)
    for label in score:
        if rappel[label] != 0 and precision[label] != 0:
            score[label] = (2 * precision[label] * rappel[label]) / (rappel[label] + precision[label])
        else:
            score[label] = 0

    return score


def draw(clusters):
    label_colors = {
        'A': '#EB4034',
        'B': '#4CC91A',
        'C': '#1AA9C9',
        'D': '#fdca40'
    }
    x = []
    y = []
    color = []
    for cluster in clusters:
        for record in cluster.records:
            x.append(record.first)
            y.append(record.second)
            color.append(label_colors[cluster.label])
    plot.scatter(x, y, c=color)
    patches = []
    for label_title in label_colors:
        patches.append(patch.Patch(color=label_colors[label_title], label=label_title))
    plot.legend(handles=patches)
    plot.show()


def start(iteration_count):
    data = pd.read_csv('dataset.csv')
    records = []
    for almost_record in data.iterrows():
        record = Record(almost_record[1]['label'], almost_record[1]['val1'], almost_record[1]['val2'])
        records.append(record)
    clusters = []
    for _ in range(4):
        centroid = records[np.random.randint(0, len(records))]  # 4 random points as clusters
        records.remove(centroid)
        clusters.append(Cluster(centroid))
    for record in records:
        cluster = get_best_cluster(record, clusters)
        cluster.add(record)

    for _ in range(iteration_count):
        iteration(clusters)

    # draw(clusters)
    print("Accuracy", compute_accuracy_index(clusters))
    print("Precision", compute_precision(clusters))
    print("Rappel", compute_rappel(clusters))
    print("Score", compute_score(clusters))


if __name__ == "__main__":
    count = int(input("Number of iterations: "))
    start(count)
