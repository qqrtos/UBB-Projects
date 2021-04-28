# -*- coding: utf-8 -*-
import math

"""
In this file your task is to write the solver function!
"""

theta_sets = {
    'NVB': [-50, -25],
    'NB': [-40, -10],
    'N': [-20, 0],
    'ZO': [-5, 5],
    'P': [0, 20],
    'PB': [10, 40],
    'PVB': [25, 50]
}

ang_speed_sets = {
    'NB': [-10, -3],
    'N': [-6, 0],
    'ZO': [-1, 1],
    'P': [0, 6],
    'PB': [3, 10]
}

force_sets = {
    'NVVB': [-40, -24],
    'NVB': [-32, -16],
    'NB': [-24, -8],
    'N': [-16, 0],
    'Z': [-4, 4],
    'P': [0, 16],
    'PB': [8, 24],
    'PVB': [16, 32],
    'PVVB': [24, 40]
}

rules_table = [
    [None, 'PB', 'P', 'ZO', 'N', 'NB'],
    ['PVB', 'PVVB', 'PVVB', 'PVB', 'PB', 'P'],
    ['PB', 'PVVB', 'PVB', 'PB', 'P', 'Z'],
    ['P', 'PVB', 'PB', 'P', 'Z', 'N'],
    ['ZO', 'PB', 'P', 'Z', 'N', 'NB'],
    ['N', 'P', 'Z', 'N', 'NB', 'NVB'],
    ['NB', 'Z', 'N', 'NB', 'NVB', 'NVVB'],
    ['NVB', 'N', 'NB', 'NVB', 'NVVB', 'NVVB']
]

rules_table_values = [
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None]
]


def triangle_formula(a, b, c, x):
    min_arg1 = (x - a) / (b - a)
    min_arg3 = (c - x) / (c - b)
    return max(0, min(min_arg1, 1, min_arg3))


def get_membership_degree(key):
    lst = []
    i = 0
    while i < len(rules_table_values):
        j = 0
        while j < len(rules_table_values[i]):
            if rules_table[i + 1][j + 1] == key:
                lst.append(rules_table_values[i][j])
            j += 1
        i += 1

    return max(lst)


def solver(t, w):
    theta_membership_degree = {}
    ang_speed_membership_degree = {}

    # compute the membership degrees for theta
    for key in theta_sets:
        a = theta_sets[key][0]
        c = theta_sets[key][1]
        b = (a + c) / 2
        theta_membership_degree[key] = triangle_formula(a, b, c, t)

    # compute the membership degrees for ang_speed
    for key in ang_speed_sets:
        a = ang_speed_sets[key][0]
        c = ang_speed_sets[key][1]
        b = (a + c) / 2
        ang_speed_membership_degree[key] = triangle_formula(a, b, c, w)

    # compute the membership of F to each set
    i = 1
    while i < len(rules_table):
        j = 1
        while j < len(rules_table[i]):
            membership_theta = theta_membership_degree[rules_table[i][0]]
            membership_ang_speed = ang_speed_membership_degree[rules_table[0][j]]
            rules_table_values[i - 1][j - 1] = min(membership_theta, membership_ang_speed)
            j += 1
        i += 1

    # compute membership degree for F
    force_membership_degree = {}
    for key in force_sets:
        force_membership_degree[key] = get_membership_degree(key)

    # defuzzify
    numerator = 0
    denominator = 0
    for key in force_membership_degree:
        value = force_membership_degree[key]
        to_multiply = (force_sets[key][0] + force_sets[key][1]) / 2
        numerator = numerator + (value * to_multiply)
        denominator = denominator + value

    try:
        return numerator / denominator
    except:
        return None
