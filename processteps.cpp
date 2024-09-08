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
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
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
    qDebug() << "setTabValRecord" << recNr;
    if(recNr >= global.tabVal.length()){
        qDebug() << "setTabVal out of range rec:" << recNr <<" l:" << global.tabVal.length();
        return;
    }
    //qDebug() << "Set rec recNr="<<recNr << recNr - firstLineIndex << " == 14  " << (global.tabVal.length() - 1) << " > "<< recNr;
    // if(((recNr - firstLineIndex ) >= 14) && ((global.tabVal.length() - 1) >  recNr ))
    // {
    //    firstLineIndex++ ;
    //    activeRow--;
    //}
    //qDebug() << "Set rec "<< activeRow << recNr << firstLineIndex;
    // UpdateTable();

    for (int i = 0; i<=14; i++){
        QLabel *label_npk = tabPtr[i].label_npk;
        //label_npk->setText(QString::number(tabVal[num].npk));

        if((i + firstLineIndex) == recNr ){

            label_npk->setStyleSheet("background:rgba(150,250,150,255);");// light green
            //label_npk->setStyleSheet("background-color:green;");// light green
            label_npk->setText(">>");
        }
        else{
            label_npk->setText(QString::number(i));
            label_npk->setStyleSheet("background:rgba(250, 250, 250, 175);"); // white
            // label_npk->setStyleSheet("background:rgba(250, 250, 250, 255);"); // white
            label_npk->setText(QString::number(i + firstLineIndex));
        }
    }
}

void ProcesSteps::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0){ // up Wheel
        on_pushButton_SlUp_clicked();
    }
    else if(event->angleDelta().y() < 0){ //down Wheel
        on_pushButton_SlDown_clicked();
    }

    // qDebug() << "Up:" << event->angleDelta().y() << "Down:" << event->angleDelta().y();

}

void ProcesSteps::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPressEvent" << event->key();
    switch (event->key()) {
    case Qt::Key_Up:
        on_pushButton_SlUp_clicked();
        break;
    case Qt::Key_Down:
        on_pushButton_SlDown_clicked();
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
            qDebug() << "loadProcesList len:" <<loadProcesList.length();
            global.tabVal.clear();
            for(int i = 0; i < loadProcesList.length(); i++){
                // qDebug() << i << "loadProcesList" <<loadProcesList[i];

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
        tableVal.npk = i;

        QLabel *label_npk = new QLabel(this);
        tablePtr.label_npk = label_npk;
        label_npk->setText(QString::number(i));
        label_npk->setMinimumSize(20, 20);


        QPushButton *button_ins = new QPushButton(this);
        tablePtr.button_ins = button_ins;
        connect(button_ins, SIGNAL(clicked()), this, SLOT(onClickIns()));
        button_ins->setText("Ins");
        button_ins->setMinimumSize(24, 24);
        button_ins->setMaximumSize(24, 24);
        button_ins->setFixedSize(24, 24);
        button_ins->setObjectName(QString::number(i));

        QPushButton *button_del = new QPushButton(this);
        tablePtr.button_del = button_del;
        connect(button_del, SIGNAL(clicked()), this, SLOT(onClickDel()));
        button_del->setText("Del");
        button_del->setMinimumSize(24, 24);
        button_del->setMaximumSize(24, 24);
        button_del->setFixedSize(24, 24);
        button_del->setObjectName(QString::number(i));

        QComboBox *cmbGroup = new QComboBox(this);
        tablePtr.cmbGroup = cmbGroup;
        cmbGroup->addItems(global.procesGroupItems);
        cmbGroup->setObjectName(QString::number(i));
        connect(cmbGroup, SIGNAL(currentIndexChanged(int)), this, SLOT(groupIndexChange(int)));
        tableVal.cmbGroupItem = 0;
        tableVal.strGroupItem = global.procesGroupItems[0];


        QComboBox *cmbObject= new QComboBox(this);
        tablePtr.cmbObject = cmbObject;
        cmbObject->addItems(global.procesObjestItemsValve);
        cmbObject->setObjectName(QString::number(i));
        cmbObject->setCurrentIndex(1);      // only for testing

        connect(cmbObject, SIGNAL(currentIndexChanged(int)), this, SLOT(objectIndexChange(int)));
        tableVal.cmbObjectItem = 0;
        tableVal.strObjectItem = global.procesObjestItemsValve[0];

        QLineEdit *linEditVal = new QLineEdit(this);
        tablePtr.linEditVal = linEditVal;
        linEditVal->setObjectName(QString::number(i));
        connect(linEditVal, SIGNAL(editingFinished()), this, SLOT(linValFinish()));
        linEditVal->setText("1");
        tableVal.val= 1;


        QLineEdit *linEditNote = new QLineEdit(this);
        tablePtr.linEditNote = linEditNote;
        linEditNote->setObjectName(QString::number(i));
        connect(linEditNote, SIGNAL(editingFinished()), this, SLOT(linNoteFinish()));
        linEditNote->setText("");
        tableVal.notes = "";

        QLabel *labelhelp = new QLabel(this);
        tablePtr.labelhelp = labelhelp;
        labelhelp->setObjectName(QString::number(i));
        QString str = "help??";
        labelhelp->setText(str);
        tabPtr.append(tablePtr);
        tableVal.helpStr = (str);

        QBoxLayout *hLayout = new QHBoxLayout(this);
        hLayout->addWidget(label_npk,0);
        hLayout->addWidget(button_ins,0);
        hLayout->addWidget(button_del,0);
        hLayout->addWidget(cmbGroup,4);
        hLayout->addWidget(cmbObject,7);
        hLayout->addWidget(linEditVal,4);
        hLayout->addWidget(linEditNote,5);
        hLayout->addWidget(labelhelp,30);

        ui->verticalLayout_4->addLayout(hLayout);
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
    label_npk->setStyleSheet("background:rgba(150,250,150,255);");// light green
    label_npk->setText(">>");

    ui->verticalSlider->setMinimum(0);
    ui->verticalSlider->setMaximum(global.tabVal.length()-1);
    ui->verticalSlider->setInvertedAppearance(false);

    ui->pushButton_SlUp->setText("\u2191");
    ui->pushButton_SlDown->setText("\u2193");

}
/*!
 * \brief ProcesSteps::UpdateTable
 *  update table data from tabVal
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
void ProcesSteps::UpdateTable()
{
    enableGroupCh = false;
        // QStringList   pipeItems;
        // pipeItems << "A" << "B";
    qDebug() << "UpdateTable:" << firstLineIndex  << activeRow << global.tabVal.length();

    // ui->verticalSlider->setMinimum(0);
    ui->verticalSlider->setMaximum((global.tabVal.length()-1));
    ui->verticalSlider->setSliderPosition(global.tabVal.length()-1 - (activeRow + firstLineIndex));

    //qDebug() << "UpdateSlider"  << 0 << activeRow <<-(global.tabVal.length()-1)<<activeRow + firstLineIndex;


    // qDebug() << "UpdateTable:"  << firstLineIndex << activeRow << global.tabVal.length() <<"eEnable:" <<enableGroupCh;

    for(int i = 0 ; i <  15; i++){

        int num = i + firstLineIndex;
        // qDebug() << "UpdateTable:"  << i << firstLineIndex << num << activeRow << global.tabVal.length();

        // QLabel *label_npk = tabPtr[i].label_npk;
        //label_npk->setText(QString::number(tabVal[num].npk));
        // label_npk->setText(QString::number(num));
        // label_npk->setStyleSheet("background:rgba(250, 250, 250, 255);"); // white


        if(num >= global.tabVal.length()){
            //  qDebug() << "UpdateTable out of tab range" << "i:" << i << "fi" <<firstLineIndex << "l:" << global.tabVal.length();

            //    QLabel *label_npk = tabPtr[i].label_npk;
            //    label_npk->setText(QString::number(num));

            QComboBox *cmbGroup = tabPtr[i].cmbGroup;   // this change tabVal[num].cmbObjectItem
            cmbGroup->setCurrentIndex(0);///(Global::GroupItems::Command);

            QComboBox *cmbObject = tabPtr[i].cmbObject;
            cmbObject->addItems(global.procesObjestItemsComand);
            cmbObject->setCurrentIndex(0);//(2);  // Stop

            QLineEdit *linEditVal = tabPtr[i].linEditVal;
            linEditVal->setText("");

            QLineEdit *linEditNote = tabPtr[i].linEditNote;
            linEditNote->setText("");

            QLabel *labelhelp = tabPtr[i].labelhelp;
            labelhelp->setText("END");
        }

        else{
            //  qDebug() << "UpdateTable in range" << "i:" << i << "fi" <<firstLineIndex << "l:" << global.tabVal.length();
            /*
                QLabel *label_npk = tabPtr[i].label_npk;
                //label_npk->setText(QString::number(tabVal[num].npk));
                label_npk->setText(QString::number(num));
                label_npk->setStyleSheet("background:rgb(250, 250, 250);"); // white
*/


            // int index  = global.tabVal[num].cmbObjectItem ;
            QComboBox *cmbGroup = tabPtr[i].cmbGroup;   // this change tabVal[num].cmbObjectItem
            cmbGroup->setCurrentIndex(global.tabVal[num].cmbGroupItem);
            global.tabVal[num].strGroupItem = cmbGroup->itemText(global.tabVal[num].cmbGroupItem);

            QComboBox *cmbObject = tabPtr[i].cmbObject;


            //qDebug() << "save tabVal[num].cmbObjectItem" << num << index << global.tabVal[num].cmbObjectItem;
            //comboBox->addItems(list);

            // qDebug() << "cmbGroup:"  <<num << global.tabVal[num].cmbGroupItem << global.tabVal[num].cmbObjectItem;
            cmbObject->clear();
            QString hstr;
            switch (global.tabVal[num].cmbGroupItem) {
            case Global::Valve: // valve
                cmbObject->addItems(global.procesObjestItemsValve);
                hstr = "Vārsts/darbība:,  signāls:,  max izpildes laiks(s):";
                break;
            case Global::Pump:  //  pump
                cmbObject->addItems(global.procesObjestItemsPump);
                hstr =  "Sūknis:, signāls 1/0:";
                break;
            case Global::DRIVES: // DRIVES
                cmbObject->addItems(global.procesObjestItemsDrives);
                hstr = "Draivs:, ātrums, ja 0 apsājas";
                break;

            case Global::IsValveFinish://  pause?
                cmbObject->addItems(global.procesObjestItemsValve);
                hstr = "Vārsts/darbība: ,gaida sign. 1/0: ,signāla vērtība:, max izpildes laiks(s):";
                break;
            case Global::Scales: // test
                cmbObject->addItems(global.procesObjestItemsScales);
                hstr = "svari: , vairāk/mazāk par:, sasniedzamā vērtība:,  Max izpildes laiks(s)";
                break;
            case Global::Tank: // test
                cmbObject->addItems(global.procesObjestItemsTank);
                hstr = "Tvertnes sensors:, Sasniedzamā vērtība:,  Max izpildes laiks(s)";
                break;
            case Global::Pipe: // Pipe
                cmbObject->addItems(global.procesObjestItemsPipe);
                hstr = "caurules bultas vieziena 0,1,2:, Vērtība:";
                break;
            case Global::Command: // Command
                cmbObject->addItems(global.procesObjestItemsComand);
                hstr = "Komandas izpildei";
                break;
            default:
                return;
                break;

            }
            // global.tabVal[num].cmbObjectItem = index ;
            // qDebug() << "restore tabVal[num].cmbObjectItem" << num  << global.tabVal[num].cmbObjectItem;
            global.tabVal[num].strObjectItem = cmbObject->itemText(global.tabVal[num].cmbObjectItem);
            cmbObject->setCurrentIndex(global.tabVal[num].cmbObjectItem);



            // cmbObject->setCurrentIndex(2);  //for testing
            //qDebug() << "set cmbObjectItem" << num << global.tabVal[num].cmbObjectItem;

            QLineEdit *linEditVal = tabPtr[i].linEditVal;
            linEditVal->setText(QString::number(global.tabVal[num].val));

            QLineEdit *linEditNote = tabPtr[i].linEditNote;
            linEditNote->setText(global.tabVal[num].notes);

            QLabel *labelHelp = tabPtr[i].labelhelp;
            global.tabVal[num].helpStr = hstr;
            labelHelp->setText(hstr);

            // tabVal
        }
    }
    qDebug() << " QLabel *label_npk "<< activeRow << tabPtr.length();
    //  QLabel *label_npk = tabPtr[activeRow].label_npk;
    //  label_npk->setStyleSheet("background:rgba(150,250,150,255);");// light green
    //label_npk->setStyleSheet("background-color:green;");// light green
    //  label_npk->setText(">>");
    setTabValRecord(activeRow);
    enableGroupCh = true;
}

void ProcesSteps::linValFinish()
{
    qDebug() << "linValFinish()" << sender();



    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        qDebug() << "linNoteFinish()" << num <<"+"<< firstLineIndex << sender()<<"L:"<< global.tabVal.length();
        QLineEdit *linEditVal = tabPtr[num].linEditVal;
        // qDebug() << "8 setTabValRecord "<< num ;
        // setTabValRecord(num);
        int val  = linEditVal->text().toInt(&ok1);
        if(ok1){
            global.tabVal[num + firstLineIndex].val = val;
            // qDebug() << "7 setTabValRecord "<< num + firstLineIndex;
            // setTabValRecord(num + firstLineIndex);
        }
    }
}

void ProcesSteps::linNoteFinish()
{
    // qDebug() << "linNoteFinish()" << num <<"+"<< firstLineIndex << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        qDebug() << "linNoteFinish()" << num <<"+"<< firstLineIndex << sender();
        QLineEdit *linEditNote = tabPtr[num].linEditNote;
        global.tabVal[num + firstLineIndex].notes  = linEditNote->text();
        qDebug() << "6 setTabValRecord "<< num + firstLineIndex;
        setTabValRecord(num + firstLineIndex);
    }
}

void ProcesSteps::onClickIns()
{
    // qDebug() << "onClickIns()" << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {

        qDebug() << "onClickIns()" << sender() << firstLineIndex << num << activeRow << global.tabVal.length();
        Global::tVal tableVal;
        global.tabVal.insert(num + firstLineIndex,tableVal);

        if(num == 14) {// last
            firstLineIndex ++;
        }
        qDebug() << "5 setTabValRecord "<< num + firstLineIndex;
        setTabValRecord(num + firstLineIndex);
        UpdateTable();

    }

}
void ProcesSteps::onClickDel()
{

    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok) {
        qDebug() << "onClickDel()"  << num << firstLineIndex << sender()<< "l:" << global.tabVal.length();


        if((global.tabVal.length() -1) == num + firstLineIndex){
            Global::tVal tableVal;
            global.tabVal.append(tableVal);
        }

        global.tabVal.removeAt(num + firstLineIndex);



     //   if((firstLineIndex == num)
     //       && (firstLineIndex != 0)){
      //      firstLineIndex--;
      //  }

        /*
         if(global.tabVal.length() < 15 + 1){
             Global::tVal tableVal;
              global.tabVal.append(tableVal);
          }
        if(firstLineIndex + 14 >= global.tabVal.length()){  // last row
            Global::tVal tableVal;
            activeRow--;
            global.tabVal.append(tableVal);
        }
*/
        qDebug() << "4 setTabValRecord "<< num + firstLineIndex;
        setTabValRecord(num + firstLineIndex);
        UpdateTable();

    }
}

void ProcesSteps::groupIndexChange(int index)
{
    //qDebug() << "groupIndexChange" << index << sender();

    if(!enableGroupCh){ // qDebug() <<"UpdateTable obj == false";
        return;
    }
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    qDebug() << "groupIndexChange" << num << firstLineIndex << index << global.tabVal.length() <<"eEnable:" <<enableGroupCh;
    if (ok && (index >= 0) && ((num + firstLineIndex) < global.tabVal.length())) {
        global.tabVal[num + firstLineIndex].cmbGroupItem = index;

        if(enableGroupCh){
            qDebug() << "3 setTabValRecord "<< num + firstLineIndex;
            setTabValRecord(num + firstLineIndex);
            UpdateTable();
        }
        else{
            qDebug() <<"UpdateTable group == false";
        }
        qDebug() << "2 setTabValRecord "<< num;
        setTabValRecord(num);
    }
}
void ProcesSteps::objectIndexChange(int index)
{
    if(!enableGroupCh){ // qDebug() <<"UpdateTable obj == false";
        return;
    }



    qDebug() << "objectIndexChange" << index << sender();
    QObject* obj = sender();
    int num = obj->objectName().toInt(&ok);
    if (ok && index >= 0) {
        qDebug() << "objectIndexChange A" << index << num << firstLineIndex << sender();
        //QComboBox *cmbObject = tabPtr[num].cmbObject;
        global.tabVal[num + firstLineIndex].cmbObjectItem = index;

        if(global.tabVal[num + firstLineIndex].cmbGroupItem == Global::IsValveFinish){
            global.tabVal[num + firstLineIndex].notes = QString().number(12);
        }

        // global.tabVal[num + firstLineIndex].strObjectItem = cmbObject->currentText();
        // qDebug() << "objectIndexChange B" << global.tabVal[num + firstLineIndex].cmbObjectItem << global.tabVal[num + firstLineIndex].strObjectItem;
        // cmbObject->setCurrentIndex(index);

        /*
        obj = sender();
        num = obj->objectName().toInt(&ok);
        if (ok > 0) {
            qDebug() << "objectIndexChange" << index << num << firstLineIndex << sender();
            QComboBox *cmbObject = tabPtr[num].cmbGroup;

            if(cmbObject->currentIndex() == Global::Pump){
                QLineEdit *linEditVal = tabPtr[num].linEditVal;
                linEditVal->setText("1");
                global.tabVal[num + firstLineIndex].val = 1;
            }
        }
        */
        qDebug() << "1 setTabValRecord "<< num + firstLineIndex;
        setTabValRecord(num + firstLineIndex);
        UpdateTable();

    }
}

void ProcesSteps::on_pushButton_SlUp_clicked()
{
    qDebug() << "Up" <<activeRow << firstLineIndex  << global.tabVal.length();
    qDebug() << "1 fi:" << firstLineIndex << "ac:" << activeRow <<"l:"<< global.tabVal.length();

    if(activeRow <= 0){
        return;
    }
    activeRow--;

    if((activeRow < firstLineIndex) > 0){
        firstLineIndex--;
        qDebug() << "first records" << global.tabVal.length() << activeRow + firstLineIndex;
    }
    qDebug() << "2 fi:" << firstLineIndex << "ac:" << activeRow <<"l:"<< global.tabVal.length();

    UpdateTable();
}


void ProcesSteps::on_pushButton_SlDown_clicked()
{
    qDebug() << "Down"<<activeRow << firstLineIndex  << global.tabVal.length();
    qDebug() << "1 fi:" << firstLineIndex << "ac:" << activeRow <<"l:"<< global.tabVal.length();

    if(activeRow >= global.tabVal.length())
    {
        qDebug() << "Out";
        return;
    }

    activeRow++;

    if((activeRow - firstLineIndex) > 14 ){
        //activeRow--;???????????????????????????????????????????
        firstLineIndex++;
        qDebug() << " no last" ;
    }
    /*
        if((activeRow + firstLineIndex)  > global.tabVal.length()-1){
        //activeRow--;
        //firstLineIndex--;
        qDebug() << "last" << global.tabVal.length() << activeRow + firstLineIndex;
    }
    */
            qDebug() << "2 fi:" << firstLineIndex << "ac:" << activeRow <<"l:"<< global.tabVal.length();

    UpdateTable();
}


void ProcesSteps::on_verticalSlider_valueChanged(int value)
{
    /*
    if(!enableGroupCh){ // qDebug() <<"UpdateTable obj == false";
        return;
    }
    // qDebug() << "Slider_valueChanged" << value << global.tabVal.length();

    if(value < global.tabVal.length()){
        setTabValRecord(value);
    }
    */
}

void ProcesSteps::on_pushButton_Start_clicked()
{
    emit startR();
}
void ProcesSteps::on_pushButton_Stop_clicked()
{
    emit stopR();
}
void ProcesSteps::on_pushButton_Pause_clicked()
{
    emit pauseR();
}


void ProcesSteps::on_pushButton_Nezxt_clicked()
{
     emit nextR();
}

