#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Shortest path.");
    setupWebEngine();
    setupSignalsAndSlots();
    displayMap();
    myGraph.initComboBoxes(ui->departComBox, ui->destComBox, ui->SearchCombox);
    setDefaultGUIValues();
}

MainWindow::~MainWindow()
{
    delete view;
    //delete channel;
    //delete page;
}

void MainWindow::setupSignalsAndSlots()
{
    connect(ui->quitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->loadButton,SIGNAL(clicked(bool)),this,SLOT(loadMap()));
}


void MainWindow::displayMap()
{
    QDir dir("map.html");
    page->load(QUrl(QUrl::fromLocalFile(dir.canonicalPath())));
}


void MainWindow::loadMap()
{
    size_t source = ui->departComBox->currentIndex();
    size_t dest = ui->destComBox->currentIndex();
    size_t searchBy = ui->SearchCombox->currentIndex();
    QString airportName, airlineName, lat, lon, javaScriptFunction;
    //if found a path
    if (myGraph.findPath(source, dest, result, searchBy)){

        //clear out the current routes.
        page->runJavaScript("clearCoord()");
        qDebug() << result.back().distance << endl;

        for (size_t i = 0 ; i < result.size() ; ++i){

            lat = QString::number(myGraph.getLat(result[i].source));
            lon = QString::number(myGraph.getLon(result[i].source));
            airportName = QString::fromStdString(myGraph.getAITA(result[i].source)) + " - ";

            if(i != 0)
                airlineName =  QString::fromStdString(myGraph.getAirlineName(result[i].airlineId));
            else
                airlineName = "Departure";

            javaScriptFunction = "addCoord (" + lat + ","+ lon + ", " + "\""
                    + airportName + airlineName + "\"" + ")";
            page->runJavaScript(javaScriptFunction);
        }
        emit drawMap();
    // if not found a path
    }else{

        string msg = "There isn't any available path from " +
                myGraph.getAirportName(source) + " to " +
                myGraph.getAirportName(dest) + ".";
        page->runJavaScript("clearCoord()");
        QMessageBox::information(this, "Warning", msg.c_str() ,QMessageBox::Ok);

    }
}

void MainWindow::setupWebEngine()
{
    qDebug()<<"starting";
    view = new QWebEngineView;
    view->setParent(ui->centralWidget);
    view->setGeometry(0,50,1600,900);
    channel = new QWebChannel(view->page());
    //attach it to the QWebEnginePage
    view->page()->setWebChannel(channel);
    //register a QObject to be exposed to JavaScript
    channel->registerObject(QStringLiteral("mainwindow"), this);
    page = view->page();
}

void MainWindow::setDefaultGUIValues(){
    // default departure -> Honolulu - HNL
    ui->departComBox->setCurrentIndex(3629);

    // default destination -> N.Y - JFK
    ui->destComBox->setCurrentIndex(3698);

    // default search -> search by shortest distance
    ui->SearchCombox->setCurrentIndex(0);
}
