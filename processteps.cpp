#include "processteps.h"
#include "qcombobox.h"
#include "qevent.h"
#include "ui_processteps.h"
#include <QFile>
#include <QFileDialog>

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

void ProcesSteps::maximizeWindow()
{
    int state = this->windowState();
    state = state & ~Qt::WindowMinimized;
    Qt::WindowState wState = static_cast<Qt::WindowState>(state);
    this->setWindowState(wState);
}

void ProcesSteps::setTabValRecord(int recNr)
{
    qDebug() << "Set rec "<< activeRow << recNr;

    int tabValRecord = activeRow + firstLineIndex;
    QLabel *label_n = tabPtr[activeRow].label_npk;
    label_n->setStyleSheet("background:rgb(255,255,255);"); // white
    label_n->setText(QString::number(tabValRecord));

    if(activeRow < 14 && tabValRecord < 14){
        activeRow = recNr;
        tabValRecord = recNr;
        label_n = tabPtr[activeRow].label_npk;
        label_n->setStyleSheet("background:rgb(150,250,150);"); // light green
        label_n->setText(">>");
    }
    else{
        firstLineIndex = recNr - 14;
        activeRow = recNr - 14;
        tabValRecord = recNr;
        label_n = tabPtr[activeRow].label_npk;
        label_n->setStyleSheet("background:rgb(150,250,150);"); // light green
        label_n->setText(">>");
    }

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
        if((activeRow + firstLineIndex) > 0){
            tabValRecord--;
            firstLineIndex--;
            qDebug() << "first records" << global.tabVal.length() << activeRow + firstLineIndex;
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
        if(activeRow + firstLineIndex < global.tabVal.length()-1){
            tabValRecord++;
            firstLineIndex++;
            qDebug() << "last records" << global.tabVal.length() << activeRow + firstLineIndex;
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

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "process.txt",
                                                    tr("Process files (*.txt)"));


    // QString path = QApplication::applicationDirPath() + "/process.txt";
    // qDebug() << "path" <<path;
    QFile file(fileName);

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly  | QIODevice::Text))
        {
            loadProcesList.clear();
            QTextStream in(&file);
            while (!in.atEnd()) {
                loadProcesList += in.readLine().split("/n");

            }

            global.tabVal.clear();
            for(int i = 0; i < loadProcesList.length(); i++){
                qDebug() << i << "loadProcesList" <<loadProcesList[i];

                QList<QString> loadPsplit = loadProcesList[i].split("|");
                qDebug() << i << "loadProcesList" <<loadProcesList[i] << loadPsplit.length() << loadPsplit;

                if(loadPsplit.length() == 1){
                    //QList<QString> loadPsplit;
                    QString str1 =  loadPsplit.at(0);
                    QStringList  str2 = str1.split(":");

                    // qDebug() << i << "loadProcesList :::"
                    //          << str2.at(0);
                    if(str2.at(0) == "NOTES")
                        ui->textEdit_Notes->setText(str1);
                    UpdateTable();
                }

                qDebug() << i << "------------------------------------" ;
                if((loadPsplit.length() != 5)  ){
                    break;
                }

                Global::tVal tabv;
                QString str;

                str = loadPsplit[0];
                int val  = str.toInt(&ok);
                if(ok){
                    tabv.npk = val;
                }
                else{
                    qDebug() << "loadProcesList[i][0]" << i << loadPsplit[0] << " = " << val;
                    break;
                    //return;
                }

                int iter = global.procesGroupItems.indexOf(loadPsplit[1]);
                tabv.cmbGroupItem = iter;   //  loadProcesList[i][1];     !!!!!!!!!!!!!!!!!!!!!!!
                qDebug() << "loadPsplit[0]" << i << loadPsplit[1] << " = " << iter
                         <<" [i][2] = ]" << loadPsplit[2];
                ///////

                switch (iter) {
                case Global::Valve: // valve
                    iter = global.procesObjestItemsValve.indexOf(loadPsplit[2]);
                    break;
                case Global::Pump: //  pump
                    iter = global.procesObjestItemsPump.indexOf(loadPsplit[2]);
                    break;
                case Global::DRIVES: // mix
                    iter = global.procesObjestItemsDrives.indexOf(loadPsplit[2]);
                    break;
                case Global::IsValveFinish: //  IsValveFinish
                    iter = global.procesObjestItemsValve.indexOf(loadPsplit[2]);
                    break;
                case Global::Scales: // test scales
                    iter = global.procesObjestItemsScales.indexOf(loadPsplit[2]);
                    break;
                case Global::Tank: // Tank
                    iter = global.procesObjestItemsTank.indexOf(loadPsplit[2]);
                    break;
                case Global::Command: // Command
                    iter = global.procesObjestItemsComand.indexOf(loadPsplit[2]);
                    break;
                case Global::Pipe: // Pipe
                    iter = global.procesObjestItemsPipe.indexOf(loadPsplit[2]);
                    break;
                default:
                    break;

                }

                ///////


                tabv.cmbObjectItem = iter;  //  loadPsplit[2];    !!!!!!!!!!!!!!!!!!!!!!!
                qDebug() << "loadPsplit[0]" << i << loadPsplit[2] << " = " << iter;

                str = loadPsplit[3]; // .value
                val  = str.toInt(&ok);
                if(ok){
                    tabv.val = val;
                }
                qDebug() << "loadPsplit[3]" << i << loadPsplit[3] << " = " << val;


                tabv.notes = loadPsplit[4];  // .notes
                qDebug() << "loadPsplit[4]" << tabv.notes;
                global.tabVal.append(tabv);
                //qDebug() << "tabv" << tabv.;
            }
            //qDebug() << "Error! 1" << global.tabVal.length() << loadProcesList.length() ;


            /*

            // load notes
            ui->textEdit_Notes->clear();
            for(int i = global.tabVal.length(); i < loadProcesList.length(); i++){
                qDebug() << "loadProcesList[i][0]"<< i << loadProcesList[i];
                ui->textEdit_Notes->append(loadProcesList[i]);
            }
*/
            activeRow = 0;
            firstLineIndex = 0;
            // UpdateTable();


        }
        else{
            qDebug() << "Error! could not open file.";
        }
    }
    else{
        // qDebug() << "Error! 3";
        //activeRow = 0;
        //firstLineIndex = 0;
        // UpdateTable();
        qDebug() << "Error! not file exist.";
    }

    UpdateTable();
}


void ProcesSteps::on_pushButton_clicked()
{
    qDebug() << "Save -----------------------------------------";   //
    // global.tabVal[num + firstLineIndex].cmbObjectItem



    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "process.txt",
                                                    tr("Process files (*.txt)"));


    saveProcesList.clear();

    for(int num = 0; num < global.tabVal.length() ; num++ ){
        QString cmdStr;
        cmdStr.append(QString::number(num));
        cmdStr.append("|");

        //QComboBox *cmbGroup = tabPtr[num].cmbGroup;
        //cmdStr.append(cmbGroup->currentText());
        //?cmdStr.append(QString().number(global.tabVal[num].cmbGroupItem));

        //cmdStr.append(global.procesGroupItems[global.tabVal[num].cmbGroupItem]);
        cmdStr.append(global.tabVal[num].strGroupItem);
        cmdStr.append("|");

        //QComboBox *cmbObject = tabPtr[num].cmbObject;
        //cmdStr.append(cmbObject->currentText());
        //?cmdStr.append(QString().number(global.tabVal[num].cmbObjectItem));


        cmdStr.append(global.tabVal[num].strObjectItem);


        cmdStr.append("|");

        // QLineEdit *linEditVal = tabPtr[num].linEditVal;
        //cmdStr.append(linEditVal->text());
        cmdStr.append(QString().number(global.tabVal[num].val));
        cmdStr.append("|");

        //QLineEdit *linEditNote = tabPtr[num].linEditNote;
        //cmdStr.append(linEditNote->text());
        cmdStr.append(global.tabVal[num].notes);
        cmdStr.append("\n");
        qDebug() << cmdStr;
        saveProcesList.append(cmdStr);

    }

    saveProcesList.append("NOTES: ");
    saveProcesList.append(ui->textEdit_Notes->toPlainText());
    saveProcesList.append("\n");

    qDebug() << "NOTES: " << ui->textEdit_Notes->toPlainText();


    //qDebug() << "path" <<path;

    //QString path = QApplication::applicationDirPath() + "/process.txt";
    //qDebug() << "path" <<path;


    QFile file(fileName);
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
    // all data in global.tabVal
    global.tabVal.clear();
    /*
     *
    struct  tVal {
        int npk = 0; //QLabel *label_npk;
        int cmbGroupItem = 0; //QComboBox *cmbGroup = nullptr;
        QString strGroupItem = "";
        int cmbObjectItem = 0;// QComboBox *cmbObject = nullptr;
        QString strObjectItem = "";
        int  val = 0;      //QLineEdit *linEditVal = nullptr;
        QString  notes = ""; //    QLineEdit *linEditNote = nullptr;
        QString helpStr = "";
    };
     *
     */
    for ( int i = 0; i<15; i++){

        tPtr tablePtr;
        Global::tVal tableVal;
        QString cmdStr;
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

        QComboBox *cmbGroup = new QComboBox(this);
        tablePtr.cmbGroup = cmbGroup;
        cmbGroup->addItems(global.procesGroupItems);
        cmbGroup->setObjectName(QString::number(npk));
        connect(cmbGroup, SIGNAL(currentIndexChanged(int)), this, SLOT(groupIndexChange(int)));
        tableVal.cmbGroupItem = 0;
        tableVal.strGroupItem = global.procesGroupItems[0];


        QComboBox *cmbObject= new QComboBox(this);
        tablePtr.cmbObject = cmbObject;
        cmbObject->addItems(global.procesObjestItemsValve);
        cmbObject->setObjectName(QString::number(npk));
        connect(cmbObject, SIGNAL(currentIndexChanged(int)), this, SLOT(objectIndexChange(int)));
        tableVal.cmbObjectItem = 0;
        tableVal.strObjectItem = global.procesObjestItemsValve[0];


        QLineEdit *linEditVal = new QLineEdit(this);
        tablePtr.linEditVal = linEditVal;
        linEditVal->setObjectName(QString::number(npk));
        connect(linEditVal, SIGNAL(editingFinished()), this, SLOT(linValFinish()));
        linEditVal->setText("1");
        tableVal.val= 1;


        QLineEdit *linEditNote = new QLineEdit(this);
        tablePtr.linEditNote = linEditNote;
        linEditNote->setObjectName(QString::number(npk));
        connect(linEditNote, SIGNAL(editingFinished()), this, SLOT(linNoteFinish()));
        linEditNote->setText("");
        tableVal.notes = "";

        QLabel *labelhelp = new QLabel(this);
        tablePtr.labelhelp = labelhelp;
        labelhelp->setObjectName(QString::number(npk));
        QString str = "Obj->Izejas signāls, V->signāla vērtība, pz->max izpildes laiks(s)";
        labelhelp->setText(str);
        tabPtr.append(tablePtr);
        tableVal.helpStr = (str);

        QBoxLayout *hLayout = new QHBoxLayout(this);
        hLayout->addWidget(label_npk,0);
        hLayout->addWidget(button_ins,0);
        hLayout->addWidget(button_del,0);
        hLayout->addWidget(cmbGroup,4);
        hLayout->addWidget(cmbObject,5);
        hLayout->addWidget(linEditVal,5);
        hLayout->addWidget(linEditNote,10);
        hLayout->addWidget(labelhelp,30);

        ui->verticalLayout_2->addLayout(hLayout);

        global.tabVal.append(tableVal);
        /*
        qDebug() << tableVal.npk
                 << tableVal.cmbGroupItem
                 <<tableVal.strGroupItem
                 << tableVal.strObjectItem;

        qDebug() << global.tabVal.last().npk
                 << global.tabVal.last().cmbGroupItem
                 << global.tabVal.last().strGroupItem
                 << global.tabVal.last().cmbObjectItem
                 << global.tabVal.last().strObjectItem
                 << global.tabVal.last().val
                 << global.tabVal.last().notes
                 << global.tabVal.last().helpStr;
*/
    }

    QLabel *label_npk = tabPtr[activeRow].label_npk;
    label_npk->setStyleSheet("background:rgb(150,250,150);");// light green
    label_npk->setText(">>");

}
/*!
 * \brief ProcesSteps::UpdateTable
 *  update table data from tabVal
 */
void ProcesSteps::UpdateTable()
{

    // QStringList   pipeItems;
    // pipeItems << "A" << "B";

    for(int i = 0 ; i <  15; i++){

        int num = i + firstLineIndex;
        qDebug() << "UpdateTable:"  << i << firstLineIndex << num << activeRow << global.tabVal.length();

        if(num >= global.tabVal.length()){
            return;
        }

        QLabel *label_npk = tabPtr[i].label_npk;
        //label_npk->setText(QString::number(tabVal[num].npk));
        label_npk->setText(QString::number(num));

        int index  = global.tabVal[num].cmbObjectItem ;
        QComboBox *cmbGroup = tabPtr[i].cmbGroup;   // this change tabVal[num].cmbObjectItem
        cmbGroup->setCurrentIndex(global.tabVal[num].cmbGroupItem);

        QComboBox *cmbObject = tabPtr[i].cmbObject;


        //qDebug() << "save tabVal[num].cmbObjectItem" << num << index << global.tabVal[num].cmbObjectItem;
        //comboBox->addItems(list);
        qDebug() << "cmbGroup:"  << global.tabVal[num].cmbGroupItem;
        cmbObject->clear();
        switch (global.tabVal[num].cmbGroupItem) {
        case Global::Valve: // valve
            cmbObject->addItems(global.procesObjestItemsValve);
            break;
        case Global::Pump:  //  pump
            cmbObject->addItems(global.procesObjestItemsPump);
            break;
        case Global::DRIVES: // DRIVES
            cmbObject->addItems(global.procesObjestItemsDrives);
            break;

        case Global::IsValveFinish://  pause?
            cmbObject->addItems(global.procesObjestItemsValve);
            break;
        case Global::Scales: // test
            cmbObject->addItems(global.procesObjestItemsScales);
            break;
        case Global::Tank: // test
            cmbObject->addItems(global.procesObjestItemsTank);
            break;


        case Global::Pipe: // Pipe
            cmbObject->addItems(global.procesObjestItemsPipe);
            break;
        case Global::Command: // Command
            cmbObject->addItems(global.procesObjestItemsComand);
            break;
        default:
            break;

        }
        global.tabVal[num].cmbObjectItem = index ;
        qDebug() << "restore tabVal[num].cmbObjectItem" << num << index << global.tabVal[num].cmbObjectItem;

        cmbObject->setCurrentIndex(global.tabVal[num].cmbObjectItem);
        qDebug() << "update tabVal[num].cmbObjectItem" << num << global.tabVal[num].cmbObjectItem;

        QLineEdit *linEditVal = tabPtr[i].linEditVal;
        linEditVal->setText(QString::number(global.tabVal[num].val));

        QLineEdit *linEditNote = tabPtr[i].linEditNote;
        linEditNote->setText(global.tabVal[num].notes);

        QLabel *labelhelp = tabPtr[i].labelhelp;
        labelhelp->setText(global.tabVal[num].helpStr);

        // tabVal
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
            global.tabVal[num + firstLineIndex].val = val;
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
        global.tabVal[num + firstLineIndex].notes  = linEditNote->text();
    }
}

void ProcesSteps::onClickIns()
{
    // qDebug() << "onClickIns()" << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        qDebug() << "onClickIns()" << sender() << num ;
        Global::tVal tableVal;
        global.tabVal.insert(num + firstLineIndex,tableVal);
        UpdateTable();
    }
}

void ProcesSteps::onClickDel()
{

    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        qDebug() << "onClickDel()"  << num << firstLineIndex << activeRow << sender();

        if(global.tabVal.length() < 16){
            Global::tVal tableVal;
            global.tabVal.append(tableVal);
        }
        else if(firstLineIndex + 14 >= global.tabVal.length()){  // last row
            Global::tVal tableVal;
            activeRow--;
            global.tabVal.append(tableVal);
        }

        global.tabVal.removeAt(num + firstLineIndex);
        UpdateTable();
    }
}

void ProcesSteps::groupIndexChange(int index)
{
    //qDebug() << "groupIndexChange" << index << sender();

    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    qDebug() << "groupIndexChange" << num << firstLineIndex << global.tabVal.length();
    if (ok && index >= 0) {
        global.tabVal[num + firstLineIndex].cmbGroupItem = index;
        global.tabVal[num + firstLineIndex].strGroupItem = global.procesGroupItems[index];


        global.tabVal[num + firstLineIndex].cmbObjectItem = 0;

        QComboBox *cmbObject = tabPtr[num].cmbObject;
        QString helpTxt;
        QLabel *labelhelp = tabPtr[num].labelhelp;
        //labelhelp->setText("???");


        cmbObject->clear();
        switch (index) {
        case Global::Valve: // valve
            cmbObject->addItems(global.procesObjestItemsValve);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsValve[0];
            global.tabVal[num + firstLineIndex].val = 1;
            helpTxt = "Obj->Izejas signāls, V->signāla vērtība, pz->max izpildes laiks(s)";
            break;
        case Global::Pump: //  pump
            cmbObject->addItems(global.procesObjestItemsPump);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsPump[0];
            helpTxt = "Ja MOHNO, drive speed +- 0.1 Hz,";
            break;
        case Global::DRIVES: // DRIVES
            cmbObject->addItems(global.procesObjestItemsDrives);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsDrives[0];
            helpTxt = "vertIbas = drive speed +- 0.1 Hz";

            break;
        case Global::IsValveFinish: //  pause?
            cmbObject->addItems(global.procesObjestItemsValve);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsValve[0];
            helpTxt = "Obj->Izejas signāls, V->signāla vērtība, pz->max izpildes laiks(s)";
            break;
        case Global::Scales: // test
            cmbObject->addItems(global.procesObjestItemsScales);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsScales[0];
            helpTxt = "V->signāla vērtība (kg)";
            break;
        case Global::Tank: // Pipe
            cmbObject->addItems(global.procesObjestItemsTank);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsTank[0];
            helpTxt = "V->signāla piepildījums(%) vai kala sensors 0|1";
            break;
        case Global::Command: // Command
            cmbObject->addItems(global.procesObjestItemsComand);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsComand[0];

            break;
        case Global::Pipe: // Pipe
            cmbObject->addItems(global.procesObjestItemsPipe);
            global.tabVal[num + firstLineIndex].strGroupItem = global.procesObjestItemsPipe[0];
            helpTxt = "flow No=0, right,down=1 left,up=2";
            break;
        default:
            break;

        }
        labelhelp->setText(helpTxt);
    }
}
void ProcesSteps::objectIndexChange(int index)
{
    //qDebug() << "objectIndexChange" << index << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok && index >= 0) {
        qDebug() << "objectIndexChange" << index << num << firstLineIndex << sender();
        QComboBox *cmbObject = tabPtr[num].cmbObject;
        global.tabVal[num + firstLineIndex].cmbObjectItem = index;
        global.tabVal[num + firstLineIndex].strObjectItem = cmbObject->currentText();
    }
}
