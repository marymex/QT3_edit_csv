# Tasks

## Task 1. Editing a csv file in a QT widget project

NOTICE. THIS TASK SHOULD ONLY BE ATTEMPTED UPON COMPLETING QT_display_csv task (DIFFERENT FROM THIS ONE).

Examine the project QT_edit_csv.pro. 
This project outputs a csv file on the form using a tableWidget as shown in the picture.

![dialog_form4](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form4.jpg)

This project also is able to edit the table when the user double-clicks a cell in it (see the picture). 

![dialog_form](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

![dialog_form2](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form2.jpg)

The user is able to save the changed file in a different .csv file by chosing the "Save" option in the menu. 

![dialog_form3](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form3.jpg)

Run the project and check this functionality.

Your task is to take the project from a DIFFERENT repository, namelly QT_display_csv (which can only display the .csv file but NOT edit)
and implement some more code so that your project can edit the .csv file too.
This QT_edit_csv project is intended to be used for reference only. 

## Adding a new form to your project

In the project that you downloaded from QT_display_csv (NOT QT_edit_csv) you can find only one form - mainwindow. 
However, QT application can contain more forms. In this project it is possible to use another form for editing the .csv table.

To edit a cell the user should double-click it which triggers another form to appear on the screen. See the picture.

![dialog_form](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

Each form typically has 3 files with code with the following extensions .h .cpp and .ui. 

To add a new form to your project you need to press "add new file" and then do the following steps (see pictures).


![adding_form1](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

![adding_form2](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

![adding_form3](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

Those acctions will result in the following files added to the project: dialog.cpp, dialog.h and dialog.ui. 

We are going to put a lineEdit on the dialog.ui form. This widget will be used for editing a cell in the table. 

![dialog1](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

## Connecting the dialog form and the mainwindow form.  

The dialog form should appear on the screen when the user double-clicks the cell. 
To make this happen we need to generate a new signal and auto-connect it with the corresponding slot function. 
Right-click the tableView and choose go to slot (see picture).

![connecting1](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

then choose double-clicked. Those actions auto-generate the function on_tableView_doubleClicked() in mainwindow.cpp:

```sh
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
}
```
To pass information from the mainwindow form to the dialog form we are going to use a static variable inside MainWindow class (mainwindow.h).
Static variables are declared with the key work static inside the class (see the picture):

![connecting2](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

However, once the static variable is declared, it needs to be set up somewhere in the memory.
In this project we set up this variable in mainwindow.cpp (see the picture)

![connecting3](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

We are going to store the address of the double-clicked tableView cell inside this static variable changedData (see picture).

![connecting4](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

The line "edit->show()" means that the dialog form will become the active window. 

Now we move on th the dialog form. The dialog form will be using the static variable "changedData" to pass new value from the user to tableView.
For this reason we need to include "mainwindow.h" in "dialog.cpp" and "dialog.h" in "mainwindow.cpp". So those 2 forms can "see" each other. 

## "Ok" and "Cancel" buttons on the dialog form. 

Now we need to generate signals: accepted from "Ok" and rejected from "Cancel" buttons on the dialog form. This action leads to two functions (dialog.cpp) being auto-generated:

![dialog2](https://github.com/marymex/QT_edit_csv/blob/main/dialog_form.jpg)

Now we change the "changedData" variable from the "on_buttonBox_accepted()" function. 
The fact that we store the adress (&) of the cell in "changedData" means that changing this variable will directly change the corresponding  cell in tableView.

```sh
void Dialog::on_buttonBox_accepted()
{
    MainWindow::changedData = ui->lineEdit->text();
    ui->lineEdit->setText() = "";
    this->close();
}
```

You need to generate the signal from the "Cancel" button on your own and impement the resulting slot function. 
Now your project should be ready. Please run it and test it. 
