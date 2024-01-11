#include "GameScene.h"


GameScene::GameScene(QObject* parent, int initialWidth, int initialHeight) :QGraphicsScene(parent), startEllipse(nullptr)
{

    Width = initialWidth;
    Height = initialHeight;
    if (!nextPlayerButton) {
        nextPlayerButton = new QPushButton("Next Player", nullptr);
        nextPlayerButton->setEnabled(false);
    }
    //drawGameBoard();
    connect(nextPlayerButton, &QPushButton::clicked, this, &GameScene::switchColor);
    piecePlaced = false;
}

void GameScene::showCoordinates(qreal x, qreal y)
{
    int X = static_cast<int>(x);
    int Y = static_cast<int>(y);

    qDebug() << "x= " << X << " y=: " << Y;
}

QPushButton* GameScene::getNextPlayerButton() const
{
    return nextPlayerButton;
}

EscapeMenuDialog* GameScene::getEscapeMenu() const
{
    return escapeMenu;
}

void GameScene::setBoardSize(int newSize)
{
    boardSize = newSize;
    drawGameBoard();
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{


    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (item && item->type() == QGraphicsEllipseItem::Type)
    {
        startEllipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        QColor color = startEllipse->data(2).value<QColor>();
        bool isOk = false;
        if (!piecePlaced)
        {
            emit circleClicked(color, startEllipse->data(1).toUInt(), startEllipse->data(0).toUInt(), isOk);
            if (isOk)
            {
                startEllipse->setBrush(currentColor);  // Face cercul rosu
                startEllipse->setData(2, currentColor);
                nextPlayerButton->setEnabled(true);
                nextPlayerButton->setStyleSheet("QPushButton {"
                    "   background-color: lightblue;"  // culoare de fundal
                    "   color: black;"                  // culoare text
                    "   border: 2px solid black;"       // grosimea bordurii ?i culoare neagr?
                    "   border-radius: 10px;"           // col?uri rotunde
                    "   padding: 5px 10px;"             // spa?iere ?ntre text ?i marginile butonului
                    "   font-family: 'Times New Roman';" // fontul textului
                    "   font-size: 12px;"               // dimensiunea fontului
                    "}");
                piecePlaced = true;
                qreal centerX = event->scenePos().x();
                qreal centerY = event->scenePos().y();

                uint16_t i = startEllipse->data(1).toUInt();  // Ia valoarea asociat? cu i
                uint16_t j = startEllipse->data(0).toUInt();  // Ia valoarea asociat? cu j


                showCoordinates(centerX, centerY);
                qDebug() << "Cerc selectat: i = " << i << ", j = " << j;
            }
        }
    }
    else if (item && item->type() == QGraphicsLineItem::Type) {
        QGraphicsLineItem* line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
        emit deleteBridgeClicked(line->data(0).toUInt(), line->data(1).toUInt(), line->data(2).toUInt(), line->data(3).toUInt());
        removeItem(item);
    }

    QGraphicsScene::mousePressEvent(event);
}


void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (startEllipse)
    {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (item && item->type() == QGraphicsEllipseItem::Type)
        {
            QGraphicsEllipseItem* endEllipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            //trebuie verificata culoarea lui endElipse
            if (endEllipse != startEllipse)
            {
                bool isOk = false;
                emit bridgeClicked(startEllipse->data(1).toUInt(), startEllipse->data(0).toUInt(), endEllipse->data(1).toUInt(), endEllipse->data(0).toUInt(), isOk);
                if (isOk)
                {
                    QGraphicsLineItem* line = new QGraphicsLineItem();
                    QPen pen(currentColor, 2, Qt::SolidLine);  // Linie ro?ie(fa tu ce culoare e), grosime 2, linie punctat?
                    line->setPen(pen);
                    line->setLine(startEllipse->rect().center().x(), startEllipse->rect().center().y(),
                        endEllipse->rect().center().x(), endEllipse->rect().center().y());
                    line->setData(0, startEllipse->data(1).toUInt());
                    line->setData(1, startEllipse->data(0).toUInt());
                    line->setData(2, endEllipse->data(1).toUInt());
                    line->setData(3, endEllipse->data(0).toUInt());
                    addItem(line);
                    lines.append(line);

                }
            }
        }


        startEllipse = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void GameScene::drawGameBoard()
{
    connect(nextPlayerButton, &QPushButton::clicked, this, &GameScene::switchColor);
    qreal buttonWidth = Width * 0.15;     // 15% din l??imea scenei
    qreal buttonHeight = Height * 0.07;; // 5% din ?n?l?imea scenei
    qreal buttonX = -Width / 2.0 + 10;;  // Ajusteaz? pozi?ia pe axa X
    qreal buttonY = -Height / 2.0 + 10;  // Ajusteaz? pozi?ia pe axa Y


    nextPlayerButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
    nextPlayerButton->setEnabled(false);

    QGraphicsDropShadowEffect* glowEffect = new QGraphicsDropShadowEffect();
    glowEffect->setBlurRadius(10);  // Ajusteaz? raza de blur pentru efectul de str?lucire
    glowEffect->setColor(Qt::red);  // Ajusteaz? culoarea pentru efectul de str?lucire
    glowEffect->setOffset(0);       // Ajusteaz? offset-ul pentru efectul de str?lucire


    qreal radius = cellSize / 4.0; // raza cercului
    qreal distance = 1.0 * cellSize; // distan?a ?ntre cercuri

    // Ini?ializarea dimensiunilor ?i coordonatelor scenei
    qreal sceneWidth = boardSize * distance;
    qreal sceneHeight = boardSize * distance;
    qreal xOffset = -sceneWidth / 2.0;
    qreal yOffset = -sceneHeight / 2.0;
   
    // Adaug? numele juc?torului 1 la stânga tablei de joc
    QGraphicsTextItem* player1TextItem = new QGraphicsTextItem(player1Name);
    player1TextItem->setFont(QFont("Arial", 12));  // Seteaz? fontul ?i dimensiunea
    player1TextItem->setDefaultTextColor(player1Color);  // Seteaz? culoarea textului
    player1TextItem->setPos(xOffset - 150, yOffset + sceneHeight / 2 - player1TextItem->boundingRect().height() / 2);
    player1TextItem->setGraphicsEffect(glowEffect);
    addItem(player1TextItem);

    // Adaug? numele juc?torului 2 la dreapta tablei de joc
    QGraphicsTextItem* player2TextItem = new QGraphicsTextItem(player2Name);
    player2TextItem->setFont(QFont("Arial", 12));  // Seteaz? fontul ?i dimensiunea
    player2TextItem->setDefaultTextColor(player2Color);  // Seteaz? culoarea textului
    player2TextItem->setPos(xOffset + sceneWidth + 50, yOffset + sceneHeight / 2 - player2TextItem->boundingRect().height() / 2);
    addItem(player2TextItem);
   
    //Adaug? numele juc?torului curent deasupra tablei de joc
    turnInfo = new QGraphicsTextItem(player1Name+"'s turn");
    turnInfo->setFont(QFont("Arial", 14));  // Seteaz? fontul ?i dimensiunea
    turnInfo->setDefaultTextColor(Qt::lightGray);  // Seteaz? culoarea textului
    turnInfo->setPos(xOffset + sceneWidth / 2 - turnInfo->boundingRect().width() / 2, yOffset - 50);  // Ajusteaz? pozi?ia pentru a fi deasupra ?i la mijlocul tablei
    addItem(turnInfo);

    // Setarea scenei
    setSceneRect(xOffset, yOffset, sceneWidth, sceneHeight);

    for (qreal i = 0; i < boardSize; ++i) {
        for (qreal j = 0; j < boardSize; ++j) {
            QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(i * distance + xOffset, j * distance + yOffset, radius, radius);
            circle->setPen(QPen(Qt::black));
            circle->setBrush(QBrush(Qt::gray));
            circle->setFlag(QGraphicsItem::ItemIsSelectable);
            circle->setData(0, i);  // ?n prima valoare (index 0), stocheaz? i
            circle->setData(1, j);  // ?n a doua valoare (index 1), stocheaz? j
            circle->setData(2, QBrush(Qt::gray)); //In a treia valoarea stocheaza culoarea
            addItem(circle);
        }
    }

    qreal lineHeight = 2.0; // Grosimea liniei
    QPen redPen(Qt::red), blackPen(Qt::black);
    redPen.setWidthF(lineHeight);
    blackPen.setWidthF(lineHeight);

    qreal middle = yOffset + distance * 0.6;
    addLine(xOffset, middle, xOffset + sceneWidth, middle, redPen);
    middle = yOffset + sceneHeight - distance * 1.3;
    addLine(xOffset, middle, xOffset + sceneWidth, middle, redPen);
    middle = xOffset + sceneWidth - distance * 1.3;
    addLine(middle, yOffset, middle, yOffset + sceneHeight, blackPen);
    middle = xOffset + distance * 0.6;
    addLine(middle, yOffset, middle, yOffset + sceneHeight, blackPen);

    lines = QList<QGraphicsLineItem*>();

    // Adaug? butonul ?n scen?
    QGraphicsProxyWidget* proxyButton = new QGraphicsProxyWidget();
    proxyButton->setWidget(nextPlayerButton);
    addItem(proxyButton);
}
void GameScene::switchColor()
{
    if (currentColor == player1Color)
    {
        currentColor = player2Color;
        turnInfo->setPlainText(player2Name+"'s turn!");
    }
    else
    {
        currentColor = player1Color;
        turnInfo->setPlainText(player1Name+"'s turn!");
    }

    nextPlayerButton->setEnabled(false);
    piecePlaced = false;
}
void GameScene::PlayersInfo(const std::string& player1Name, QColor color1, const std::string& player2Name, QColor color2)
{
    player1Color = color1;
    player2Color = color2;
    this->player1Name = QString::fromStdString(player1Name);
    this->player2Name = QString::fromStdString(player2Name);
    currentColor = player1Color;
}
void GameScene::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        
        escapeMenu->exec();
    }
    else {
        QGraphicsScene::keyPressEvent(event);
    }
}
}
void GameScene::onBoardLoaded(const Board& loadedBoard)
{
    clear();
    qreal radius = cellSize / 4.0; // raza cercului
    qreal distance = 1.0 * cellSize; // distan?a ?ntre cercuri

    // Ini?ializarea dimensiunilor ?i coordonatelor scenei
    qreal sceneWidth = loadedBoard.getSize()* distance;
    qreal sceneHeight = loadedBoard.getSize()* distance;
    qreal xOffset = -sceneWidth / 2.0;
    qreal yOffset = -sceneHeight / 2.0;
    setSceneRect(xOffset, yOffset, sceneWidth, sceneHeight);
    for (qreal i = 0; i < loadedBoard.getSize(); ++i)
    {
        for (qreal j = 0; j < loadedBoard.getSize(); ++j)
        {
            QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(i * distance + xOffset, j * distance + yOffset, radius, radius);
            circle->setPen(QPen(Qt::black));
             QColor cellColor = loadedBoard(i,j).getColor();
            circle->setBrush(QBrush(cellColor));
            circle->setFlag(QGraphicsItem::ItemIsSelectable);
            circle->setData(0, i);  // ?n prima valoare (index 0), stocheaz? i
            circle->setData(1, j);  // ?n a doua valoare (index 1), stocheaz? j
            circle->setData(2, QBrush(cellColor)); //In a treia valoarea stocheaza culoarea

            addItem(circle);
        }
    }
    qreal lineHeight = 2.0; // Grosimea liniei
    QPen redPen(Qt::red), blackPen(Qt::black);
    redPen.setWidthF(lineHeight);
    blackPen.setWidthF(lineHeight);

    qreal middle = yOffset + distance * 0.6;
    addLine(xOffset, middle, xOffset + sceneWidth, middle, redPen);
    middle = yOffset + sceneHeight - distance * 1.3;
    addLine(xOffset, middle, xOffset + sceneWidth, middle, redPen);
    middle = xOffset + sceneWidth - distance * 1.3;
    addLine(middle, yOffset, middle, yOffset + sceneHeight, blackPen);
    middle = xOffset + distance * 0.6;
    addLine(middle, yOffset, middle, yOffset + sceneHeight, blackPen);

    lines = QList<QGraphicsLineItem*>();

}