# Tasks

## Task 1. Editing a csv file in a QT widget project

NOTICE. THIS TASK SHOULD ONLY BE ATTEMPTED UPON COMPLETING QT_display_csv task (DIFFERENT FROM THIS ONE).

Examine the project QT_edit_csv.pro. 
This project outputs a csv file on the form using a tableWidget as shown in the picture.

![form_with_data](https://github.com/marymex/QT_display_csv/blob/main/form_with_data.jpg)

This project also is able to edit the table when the user double-clicks a cell in it (see the picture). 

![form_with_data](https://github.com/marymex/QT_display_csv/blob/main/form_with_data.jpg)

The user is able to save the changed file in a different .csv file by chosing the "Save" option in the menu. 

![form_with_data](https://github.com/marymex/QT_display_csv/blob/main/form_with_data.jpg)

Run the project and check this functionality.

Your task is to take the project from a DIFFERENT repository, namelly QT_display_csv (which can only display the .csv file but NOT edit)
and implement some more code so that your project can edit the .csv file too.


In the project there a .csv files. The task is to display this file in a QT Widgets project (on the picture above). 

This project is intended to be used for reference only. 
The task is to create an empty QT project from scratch following the steps bellow. 

### Designer

Modify the interface of your project using QT Designer.

Examine the form.jpeg picture. It shows the arrangement of the widgets.

![form](https://github.com/marymex/QT_display_csv/blob/main/form.jpg)

1. Add a vertical layout on your form.

2. Inside the layout add a tableView and a lineEdit.

The tableView widget will be used to display the .csv file on the form.
The lineEdit widget will be used for logging. 

It is desirable to use layouts in your project for style and functionality. 
However, if you are having trouble with the layout you can skip the layout setup for now and return to it later.

3. Add a menu "File" on your form ("write here" option at the top). Inside the menu add two options: "Open" and "Save".

### Slots and signal

In QT some widgets send signals when the user is interracting with the form and some other widgets catch those signals.
To catch a signal send by one widget, another widget has a function called "slot function". Now we are going to set some slot functions for some widget signals. 

When the user clicks on the menubar, choosing the option "Open" there should be a fileDialogue window which allows the user to choose the .csv file for display. 

Examine the picture choosing_signal_for_the_menu_bar.jpeg for reference. 

![chosing_signal_for%20the_menu_bar](https://github.com/marymex/QT_display_csv/blob/main/chosing_signal_for%20the_menu_bar.jpg)

Right-mouth-click on actionOpen (this is a signal) -> go to slot -> triggered().  

![slot-function-added](https://github.com/marymex/QT_display_csv/blob/main/slot-function-added.jpg)

Those actions auto-generate some code in mainwindow.cpp and mainwindow.h. Namely, they add a slot function which will be run when the user clicks on the "Open option of the menu". 
In mainwindow.h we can find the declaration of a new function: 

```sh
void on_actionOpen_2_triggered();
```

In mainwindow.cpp (NOTE, this file is NOT mainwindow.h) we see the body of the function:

```sh
void MainWindow::on_actionOpen_2_triggered()
{

}
```

Inside the body of the function we write code which will be executed when we click on the button.

Simularly, we need to generate a slot-function for the "Save" option.

### Reading data 

When the user clicks on the menubar, choosing the option "Open" there should be a fileDialogue window which allows the user to choose the csv file for display. 
For this purpose we need to write the following code in on_actionOpen_2_triggered():  

```sh
void MainWindow::on_actionOpen_2_triggered()
{
    // OPEN FILE
    inputFile = QFileDialog::getOpenFileName(this, "Choose file format .csv", QDir::currentPath());
    ui->lineEdit->setText("input file loaded");
    QApplication::processEvents();

    // LOAD THE CSV FILE in _data and _headers
    try
    {
     loadCSV(inputFile, _data, _headers);
    }
    catch (const std::runtime_error& e)
    {
       QMessageBox::warning(this, "Error", "Could not open file");
    }
    ui->lineEdit->setText("data read");
    QApplication::processEvents();

    // SET UP a MODEL FOR TABLEVIEW
    model = new table_model(_data, _headers, nullptr);
    ui->tableView->setModel(model);
    ui->lineEdit->setText("data displayed");
    QApplication::processEvents();
}
```

At this point you might not be understanding the code of this function. You need to look at it carefully and try to understand it as you continue to work on this task (going back and forth in this manual). 
You will be understanding it bit by bit as you go along.  
The next part of the task is implementing the loadCSV() function. 
This function takes the input file name and reads it into "data" and "headers" containers.
Later on, those two containers will be used to set the model for the tableView widget. 
That is done in a separate source file - "readwrite.cpp":

```sh
void loadCSV(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers)
{
    // OPEN THE FILE
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //QMessageBox::warning(this, "Error", "Could not open file");
        throw std::runtime_error("Could not open file");
    }

    // READ DATA to data and headers
    QTextStream stream(&file);
    data.clear();
    QString hh = stream.readLine();
    headers = hh.split(',');

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');
        QList<QString> cur;
        for(int i = 0; i < fields.size(); i++)
            cur.append(fields[i]);

        data.push_back(cur);
    }

    file.close();
}
```

In "readwrite.h" you can find the declaration of this function. 

```sh
void loadCSV(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers);
```
You can notice that in this function the fields "data" and "headers" are passed by reference (&). 
Those fields are declaredd in mainwindow.h as member-fields of the mainwindow class (examile mainwindow.cpp and find them).
We use those fields to store data from the .csv table. Similarly, these containers are used to set up the model for the tableView widget. 

Now look at the void MainWindow::on_actionOpen_2_triggered() function again. It has the block: "// SET UP a MODEL FOR TABLEVIEW":

```sh
   // SET UP a MODEL FOR TABLEVIEW
    model = new table_model(_data, _headers, nullptr);
    ui->tableView->setModel(model);
    ui->lineEdit->setText("data displayed");
    QApplication::processEvents();
```

Those code lines describe setting up a model for the TableVieW widget.
However, in those lines we create an object of some class "table_model" which we did not declare or implement yet.

### Implementing model for tableView (MV approach)

Now we are going to correct this by implementing "table_model" class. 
This class is a special "layer" between tableView widget and the data stored in the containers "data" and "headers". 
You can add this class by adding a new class in your project. Examine the pictures for better understanding. 

![QT_choosing_model.jpg](https://github.com/marymex/QT_display_csv/blob/main/QT_choosing_model.jpg)

![QT_choosing_model2](https://github.com/marymex/QT_display_csv/blob/main/QT_choosing_model2.jpg)

Name your class table_model. As you do that you will see two new filed got added to your project.
Namely, table_model.h and table_model.cpp.
First those two files have unfinished functions in them.
You need to implement those functions like this:

```sh
table_model::table_model(const QList<QList<QString> >& ddata, const QList<QString>& hheaders, QObject *parent)
    : QAbstractTableModel(parent), _data(ddata), _headers(hheaders)
{
  // constructor
}

QVariant table_model::headerData(int section, Qt::Orientation orientation, int role) const
{
   // access to headers 
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return _headers.at(section);
    else
        return section + 1;
}

int table_model::rowCount(const QModelIndex &parent) const
{
  // access to row count
    if (parent.isValid())
        return 0;

    return _data.size();
}

int table_model::columnCount(const QModelIndex &parent) const
{
  // access to column count
    if (parent.isValid())
        return 0;

    if (_data.size()==0)
        return 0;

    return _data[0].count();
}

QVariant table_model::data(const QModelIndex &index, int role) const
{
  // access to data
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    return _data[index.row()][index.column()] ;
}
```

Those functions are inherited from the class QAbstractTableModel and they are overloaded. 
You can understand this fact by looking at the "override" notes against every such function in table_model.h

```sh
class table_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit table_model(const QList<QList<QString> >& mdata, const QList<QString>& hheaders, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override; // HERE

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override; // HERE
    int columnCount(const QModelIndex &parent = QModelIndex()) const override; // HERE

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override; // HERE

private:
    const QList<QList<QString> >& _data;
    const QList<QString>& _headers;
};
```

Those functions provide functionality to the model which acts basically as an interface for data display on the tableView widget.
So you can imagine that there is a "hidden" class "QAbstractTableModel" which is inherited and it has some functionality which is used by the tableView model but not really seen.

At this point we ended the first part of the project which deals with "Open" option of the menu. Now the applications should be able to display the table.
You can try to run it and check. Possible you will encounter some difficulties in the process. 
However, try to overcome them and use assistant teacher, your friends or chatGPT for help. Reread this manual as you do it.


### Saving data

The second part of this project is saving the table. 
At this point the table cannot be edited so saving will only generate a copy of the original file. 
Editing of the table will be considered later. 
For now let's imagine that we somehow edited the table through the tableView widget and we intend to save it in a different .csv file.
Saving the table means taking data from the "data" and "headers" containers and writing it into a .csv file.  

First, You need to generate a slot function for triggering the "Save" option of the menu and implement it.
The code in mainwindow.cpp looks like this:

```sh
void MainWindow::on_actionSave_2_triggered()
{
    QString outputFile = QFileDialog::getSaveFileName(this, "Choose file format .csv", QDir::currentPath());
    ui->lineEdit->setText("output file loaded");
    QApplication::processEvents();

    try
    {
        saveTableToFile(outputFile, _data, _headers);
    }
    catch (const std::runtime_error& e)
    {
        QMessageBox::warning(this, "Error", "Could not save file");
    }

    ui->lineEdit->setText("data saved");
    QApplication::processEvents();
}
```

The code in mainwindow.h looks like this:

```sh
void on_actionSave_2_triggered();
```

You might notice that the function for saving the file is called safeTableToFile().
We need to implement it in readwrite.cpp 
Those two files readwrite.cpp and readwrite.h are used to store functions for reading and writing data.

Declare the safeTableToFile() function in readwrite.h

```sh
void saveTableToFile(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers);
```

Implement this function in readwrite.cpp:

```sh
void saveTableToFile(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers)
{
    // OPEN FILE
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw std::runtime_error("Could not open file");
    }

    // WRITE DATA IN THE FILE
    QTextStream stream(&file);
    stream << headers.join(',') << "\n";

    for (int row = 0; row < data.size(); ++row)
        stream << data[row].join(',') << "\n";

    file.close();
}
```

Now your project should be ready. Run it and test it. 

