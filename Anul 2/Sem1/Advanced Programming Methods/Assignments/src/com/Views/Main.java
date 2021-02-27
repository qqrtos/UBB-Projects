package com.Views;

import Controllers.Controller;
import Exceptions.CustomException;
import Models.*;
import Models.IEntity;
import Repository.ArrayRepository;
import Repository.IRepository;

public class Main {

    public static void main(String[] args) {
        /* Instantiate some elements */
        IEntity e2 = new Turtle(15);
        IEntity e3 = new Turtle(0);
        IEntity e4 = new Fish(0);
        IEntity e5 = new Fish(6);
        IEntity e1 = new Turtle(32);

        IRepository repository = new ArrayRepository(5);
        Controller controller = new Controller(repository);

        try {
            controller.add(e1);
            controller.add(e2);
            controller.add(e3);
            controller.add(e4);
            controller.add(e5);
        } catch (CustomException ex) {
            System.out.println("Exception " + ex.getMessage() + " occurred.");
        }

        int minAge = 1;
        IEntity[] filteredByAge = controller.filterByAge(minAge);

        for (IEntity item : filteredByAge) {
            if (item == null){
                break;
            }

            System.out.println(item.toString());
        }
    }
}
