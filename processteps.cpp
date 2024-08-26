#include "processteps.h"
#include "qcombobox.h"
#include "qevent.h"
#include "ui_processteps.h"
#include <QFile>

ProcesSteps::ProcesSteps(Global& global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::ProcesSteps)
{
    ui->setupUi(this);
    drawWidgets();
}

ProcesSteps::~ProcesSteps()
{
    delete ui;
}

void ProcesSteps::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0){ // up Wheel
        on_pushButton_Up_clicked();
    }
    else if(event->angleDelta().y() < 0){ //down Wheel
        on_pushButton_Down_clicked();
    }
}

void ProcesSteps::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPressEvent" << event->key();
    switch (event->key()) {
    case Qt::Key_Up:
        on_pushButton_Up_clicked();
        break;
    case Qt::Key_Down:
        on_pushButton_Down_clicked();
        break;
    case Qt::Key_Delete:
        //  onClickDel(); row?
        break;
    case Qt::Key_Insert:
        //onClickIns(); //row?
        break;
    default:
        break;
    }


}

void ProcesSteps::on_pushButton_Up_clicked()
{
    qDebug() << "UP";

    int tabValRecord = activeRow + firstLineIndex;

    QLabel *label_n = tabPtr[activeRow].label_npk;
    label_n->setStyleSheet("background:rgb(255,255,255);"); // white
    label_n->setText(QString::number(tabValRecord));

    if(activeRow > 0){
        activeRow--;
        tabValRecord--;
        label_n = tabPtr[activeRow].label_npk;
        label_n->setStyleSheet("background:rgb(150,250,150);"); // light green
        label_n->setText(">>");
    }
    else{
        if(activeRow + firstLineIndex > 0){
            tabValRecord--;
            firstLineIndex--;
            qDebug() << "first records" << tabVal.length() << activeRow + firstLineIndex;
        }
        //  label_n = tabPtr[activeRow].label_npk;
        //  label_n->setStyleSheet("background:rgb(150,250,150);"); // light green
        //  label_n->setText(">>");
        UpdateTable();
    }
}


void ProcesSteps::on_pushButton_Down_clicked()
{
    qDebug() << "Down"<<activeRow << firstLineIndex;

    int tabValRecord = activeRow + firstLineIndex;

    QLabel *label_n = tabPtr[activeRow].label_npk;
    label_n->setStyleSheet("background:rgb(255,255,255);"); // white
    label_n->setText(QString::number(tabValRecord));

    if(activeRow < 14){
        activeRow++;
        tabValRecord++;
        label_n = tabPtr[activeRow].label_npk;
        label_n->setStyleSheet("background:rgb(150,250,150);"); // light green
        label_n->setText(">>");
    }
    else{
        if(activeRow + firstLineIndex < tabVal.length()-1){
            tabValRecord++;
            firstLineIndex++;
            qDebug() << "last records" << tabVal.length() << activeRow + firstLineIndex;
        }
        //  label_n = tabPtr[activeRow].label_npk;
        //  label_n->setStyleSheet("background:rgb(150,250,150);"); // light green
        //  label_n->setText(">>");
        UpdateTable();
    }
}


void ProcesSteps::on_pushButton_Load_clicked()
{
    qDebug() << "Load";
    QString path = QApplication::applicationDirPath() + "/process.txt";
    qDebug() << "path" <<path;
    QFile file(path);

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly  | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                loadProcesList += in.readLine().split("/n");
            }
            //qDebug() << "loadProcesList" << loadProcesList;

            tabVal.clear();
            for(int i = 0; i < loadProcesList.length(); i++){
                qDebug() << loadProcesList[i];
                tVal tabv;
                QString str;

                str = loadProcesList[i][0];
                int val  = str.toInt(&ok);
                if(ok){
                    tabv.npk = val;
                }
                else{
                    qDebug() << "loadProcesList[i][0]" << i << loadProcesList[i][0];
                    break;
                    //return;
                }

                tabv.cmbGroupItem = 0;   //  loadProcesList[i][1];     !!!!!!!!!!!!!!!!!!!!!!!
                tabv.cmbObjectItem = 0;  //  loadProcesList[i][2];    !!!!!!!!!!!!!!!!!!!!!!!


                str = loadProcesList[i][3];
                val  = str.toInt(&ok);
                if(ok){
                    tabv.val = val;
                }

                tabv.notes = loadProcesList[i][4];
                tabVal.append(tabv);
            }
            qDebug() << "Error! 1" << tabVal.length() << loadProcesList.length() ;

            // load notes
            ui->textEdit_Notes->clear();
            for(int i = tabVal.length(); i < loadProcesList.length(); i++){
                qDebug() << "loadProcesList[i][0]"<< i << loadProcesList[i];
                ui->textEdit_Notes->append(loadProcesList[i]);
            }

            activeRow = 0;
            firstLineIndex = 0;
            UpdateTable();


        }
        else{
            qDebug() << "Error! could not open file.";
        }
        // qDebug() << "Error! 2";
    }
    // qDebug() << "Error! 3";
    //activeRow = 0;
    //firstLineIndex = 0;
    // UpdateTable();
}


void ProcesSteps::on_pushButton_clicked()
{
    qDebug() << "Save";
    saveProcesList.clear();

    for(int num = 0; num < tabVal.length() ; num++ ){
        QString cmdStr;
        cmdStr.append(QString::number(num));
        cmdStr.append(",");

        QComboBox *cmbGroup = tabPtr[num].cmbGroup;
        cmdStr.append(cmbGroup->currentText());
        cmdStr.append(",");

        QComboBox *cmbObject = tabPtr[num].cmbObject;
        cmdStr.append(cmbObject->currentText());
        cmdStr.append(",");

        QLineEdit *linEditVal = tabPtr[num].linEditVal;
        cmdStr.append(linEditVal->text());
        cmdStr.append(",");

        QLineEdit *linEditNote = tabPtr[num].linEditNote;
        cmdStr.append(linEditNote->text());
        cmdStr.append("\n");
        // qDebug() << cmdStr;
        saveProcesList.append(cmdStr);
    }

    saveProcesList.append("NOTES: ");
    saveProcesList.append(ui->textEdit_Notes->toPlainText());
    saveProcesList.append("\n");

    qDebug() << saveProcesList;


    //QDataStream
    //QTextStream


    QString path = QApplication::applicationDirPath() + "/process.txt";
    qDebug() << "path" <<path;
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error! could not open file.";

    }
    else{
        QTextStream out(&file);

        foreach(QString process, saveProcesList) {
            out << process;
        }

        file.close();
    }
    /*
    //for testing

    QComboBox *cmbObject = tabPtr[10].cmbObject;
    //cmbObject->addItems({ "Valve 1", "Valve 2", "Valve 3", "Valve 4","Valve 5" });
    cmbObject->setCurrentText("Valve 2");
    qDebug() << "cmbObject->currentIndex(Valve 2)" << cmbObject->currentIndex();
    cmbObject->setCurrentText("Valve 3");
    qDebug() << "cmbObject->currentIndex(Valve 3)" << cmbObject->currentIndex();
    cmbObject->setCurrentText("V");
    qDebug() << "cmbObject->currentIndex(V)" << cmbObject->currentIndex();
    */
}


void ProcesSteps::on_textEdit_Notes_textChanged()
{
    qDebug() << "Notes_textChanged"  << ui->textEdit_Notes->toPlainText();
}

void ProcesSteps::drawWidgets()
{
    int npk = 0;

    for ( int i = 0; i<15; i++){

        tPtr tablePtr;
        tVal tableVal;
        signalMapper = new QSignalMapper(this);
        npk = i;
        tableVal.npk = i;

        QLabel *label_npk = new QLabel(this);
        tablePtr.label_npk = label_npk;
        label_npk->setText(QString::number(npk));
        label_npk->setMinimumSize(20, 20);


        QPushButton *button_ins = new QPushButton(this);
        tablePtr.button_ins = button_ins;
        connect(button_ins, SIGNAL(clicked()), this, SLOT(onClickIns()));
        button_ins->setText("Ins");
        button_ins->setMinimumSize(24, 24);
        button_ins->setMaximumSize(24, 24);
        button_ins->setFixedSize(24, 24);
        button_ins->setObjectName(QString::number(npk));

        QPushButton *button_del = new QPushButton(this);
        tablePtr.button_del = button_del;
        connect(button_del, SIGNAL(clicked()), this, SLOT(onClickDel()));
        button_del->setText("Del");
        button_del->setMinimumSize(24, 24);
        button_del->setMaximumSize(24, 24);
        button_del->setFixedSize(24, 24);
        button_del->setObjectName(QString::number(npk));

        QComboBox *cmbGroup = new QComboBox;
        tablePtr.cmbGroup = cmbGroup;
        cmbGroup->addItems({ "Valve", "Pump", "Mix", "Pause","Test","Pipe" });
        cmbGroup->setObjectName(QString::number(npk));
        connect(cmbGroup, SIGNAL(currentIndexChanged(int)), this, SLOT(groupIndexChange(int)));

        QComboBox *cmbObject= new QComboBox;
        tablePtr.cmbObject = cmbObject;
        cmbObject->addItems({ "Valve 1", "Valve 2", "Valve 3", "Valve 4","Valve 5" });
        cmbObject->setObjectName(QString::number(npk));
        connect(cmbObject, SIGNAL(currentIndexChanged(int)), this, SLOT(objectIndexChange(int)));

        QLineEdit *linEditVal = new QLineEdit();
        tablePtr.linEditVal = linEditVal;
        linEditVal->setObjectName(QString::number(npk));
        connect(linEditVal, SIGNAL(editingFinished()), this, SLOT(linValFinish()));
        linEditVal->setText("0");

        QLineEdit *linEditNote = new QLineEdit();
        tablePtr.linEditNote = linEditNote;
        linEditNote->setObjectName(QString::number(npk));
        connect(linEditNote, SIGNAL(editingFinished()), this, SLOT(linNoteFinish()));
        linEditNote->setText("0");

        tabPtr.append(tablePtr);
        tabVal.append(tableVal);

        QBoxLayout *hLayout = new QHBoxLayout(this);
        hLayout->addWidget(label_npk,0);
        hLayout->addWidget(button_ins,0);
        hLayout->addWidget(button_del,0);
        hLayout->addWidget(cmbGroup,4);
        hLayout->addWidget(cmbObject,5);
        hLayout->addWidget(linEditVal,5);
        hLayout->addWidget(linEditNote,10);

        ui->verticalLayout_2->addLayout(hLayout);

    }

    QLabel *label_npk = tabPtr[activeRow].label_npk;;
    label_npk->setStyleSheet("background:rgb(150,250,150);");// light green
    label_npk->setText(">>");

}

void ProcesSteps::UpdateTable()
{

    QStringList   pipeItems;
    pipeItems << "A" << "B";

    for(int i = 0 ; i <  15; i++){

        int num = i + firstLineIndex;
        qDebug() << "UpdateTable:"  << i << num << tabVal.length();
        QLabel *label_npk = tabPtr[i].label_npk;
        //label_npk->setText(QString::number(tabVal[num].npk));
        label_npk->setText(QString::number(num));

        int index  = tabVal[num].cmbObjectItem ;
        QComboBox *cmbGroup = tabPtr[i].cmbGroup;   // this change tabVal[num].cmbObjectItem
        cmbGroup->setCurrentIndex(tabVal[num].cmbGroupItem);

        QComboBox *cmbObject = tabPtr[i].cmbObject;


        qDebug() << "save tabVal[num].cmbObjectItem" << num << index << tabVal[num].cmbObjectItem;
        //comboBox->addItems(list);
        qDebug() << "cmbGroup:"  << tabVal[num].cmbGroupItem;
        cmbObject->clear();
        switch (tabVal[num].cmbGroupItem) {
        case 0: // valve
            cmbObject->addItems({ "Valve 1", "Valve 2", "Valve 3", "Valve 4","Valve 5" });
            break;
        case 1: //  pump
            cmbObject->addItems({ "Pump 1", "Pump 2", "Pump 3", "Pump 4","Pump 5" });
            break;
        case 2: // mix
            cmbObject->addItems({ "Mix 1"});
            break;
        case 3: //  pause
            cmbObject->addItems({ "pause" });
            break;
        case 4: // test
            cmbObject->addItems({ "test"});
            break;
        case 5: // Pipe
            cmbObject->addItems({ "test1"});
            break;
        default:
            break;

        }
        tabVal[num].cmbObjectItem = index ;
        qDebug() << "restore tabVal[num].cmbObjectItem" << num << index << tabVal[num].cmbObjectItem;

        cmbObject->setCurrentIndex(tabVal[num].cmbObjectItem);
        qDebug() << "update tabVal[num].cmbObjectItem" << num << tabVal[num].cmbObjectItem;

        QLineEdit *linEditVal = tabPtr[i].linEditVal;
        linEditVal->setText(QString::number(tabVal[num].val));

        QLineEdit *linEditNote = tabPtr[i].linEditNote;
        linEditNote->setText(tabVal[num].notes);
    }
    QLabel *label_npk = tabPtr[activeRow].label_npk;
    label_npk->setStyleSheet("background:rgb(150,250,150);"); // light green
    label_npk->setText(">>");
}

void ProcesSteps::linValFinish()
{
    qDebug() << "linValFinish()" << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        QLineEdit *linEditVal = tabPtr[num].linEditVal;

        int val  = linEditVal->text().toInt(&ok1);
        if(ok1){
            tabVal[num + firstLineIndex].val = val;
        }
    }
}

void ProcesSteps::linNoteFinish()
{
    qDebug() << "linNoteFinish()" << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        QLineEdit *linEditNote = tabPtr[num].linEditNote;
        tabVal[num + firstLineIndex].notes  = linEditNote->text();
    }
}

void ProcesSteps::onClickIns()
{
    // qDebug() << "onClickIns()" << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        qDebug() << "onClickIns()" << sender() << num ;
        tVal tableVal;
        tabVal.insert(num,tableVal);
        UpdateTable();
    }
}

void ProcesSteps::onClickDel()
{

    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        qDebug() << "onClickDel()" << num << tabVal.length();

        if(tabVal.length() < 16){
            tVal tableVal;
            tabVal.append(tableVal);
        }
        tabVal.removeAt(num);

        UpdateTable();

    }
}

void ProcesSteps::groupIndexChange(int index)
{
    qDebug() << "groupIndexChange" << index << sender();

    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        tabVal[num + firstLineIndex].cmbGroupItem = index;
        QComboBox *cmbObject = tabPtr[num].cmbObject;


        //comboBox->addItems(list);
        qDebug() << "cmbGroup:"  <<num << index;
        cmbObject->clear();
        switch (index) {
        case 0: // valve
            cmbObject->addItems({ "Valve 1", "Valve 2", "Valve 3", "Valve 4","Valve 5" });
            break;
        case 1: //  pump
            cmbObject->addItems({ "Pump 1", "Pump 2", "Pump 3", "Pump 4","Pump 5" });
            break;
        case 2: // mix
            cmbObject->addItems({ "Mix 1"});
            break;
        case 3: //  pause
            cmbObject->addItems({ "sek." });
            break;
        case 4: // test
            cmbObject->addItems({ "test"});
            break;
        case 5: // Pipe
            cmbObject->addItems(global.pipeItems);
            break;
        default:
            break;
        }
    }





}

void ProcesSteps::objectIndexChange(int index)
{
    //qDebug() << "objectIndexChange" << index << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        if(index >= 0){
            tabVal[num + firstLineIndex].cmbObjectItem = index;
            qDebug() << "objectIndexChange" << index << num;
        }
    }
}
