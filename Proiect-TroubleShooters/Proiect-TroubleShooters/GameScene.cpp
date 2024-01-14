#include "GameScene.h"
#define BUTTON_ENABLED_STYLE "QPushButton {" \
"    background-color: #7B7B7B;" \
"    color: white;" \
"    border: 2px solid #343434;" \
"    border-radius: 8px;" \
"    padding: 4px 8px;" \
"}" \
"QPushButton:hover {" \
"    background-color: #555555;" \
"}"

#define BUTTON_DISABLED_STYLE "QPushButton {" \
"    background-color: #D1D1D1;" \
"    color: #A6A6A6;" \
"    border: 2px solid #B0B0B0;" \
"    border-radius: 8px;" \
"    padding: 4px 8px;" \
"}" \
"QPushButton:hover {" \
"    background-color: #555555;" \
"}"


GameScene::GameScene(QObject* parent, int initialWidth, int initialHeight) :QGraphicsScene(parent), startEllipse(nullptr)
{

    Width = initialWidth;
    Height = initialHeight;
    if (!nextPlayerButton) {
        nextPlayerButton = new QPushButton("Next Player", nullptr);
        nextPlayerButton->setEnabled(false);
        nextPlayerButton->setStyleSheet(BUTTON_DISABLED_STYLE);
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
bool GameScene::isPointInsideEllipse(const QPointF& point,  QGraphicsEllipseItem* ellipse)
{
    return ellipse->rect().contains(point);
}
void GameScene::applyGlowEffect(QGraphicsTextItem* textItem, int blurRadius, const QColor& glowColor, int offset)
{
    if (!textItem || !textItem->scene()) {
        return;
    }

    // Creează un efect de umbră cu parametrii personalizați
    QGraphicsDropShadowEffect* glowEffect = new QGraphicsDropShadowEffect;
    glowEffect->setBlurRadius(blurRadius);  // Raza de blur
    glowEffect->setColor(glowColor);        // Culoarea umbrei
    glowEffect->setOffset(offset);          // Offsetul umbrei

    // Aplică efectul de umbră pe QGraphicsTextItem
    textItem->setGraphicsEffect(glowEffect);
}
bool GameScene::isPointInsideAnyEllipse(const QPointF& point, QList<QGraphicsEllipseItem*>& ellipses)
{
    for (QGraphicsEllipseItem* ellipse : ellipses) {
        if (isPointInsideEllipse(point, ellipse)) {
            return true;
        }
    }
    return false;
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
                nextPlayerButton->setStyleSheet(BUTTON_DISABLED_STYLE);
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
        QPen pen = line->pen();
        QColor lineColor = pen.color();

        
        QPointF clickPos = event->scenePos();
        if (!isPointInsideAnyEllipse(clickPos, circlesList) && lineColor==currentColor) {
            emit deleteBridgeClicked(line->data(0).toUInt(), line->data(1).toUInt(), line->data(2).toUInt(), line->data(3).toUInt());
            removeItem(item);
        }
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
   

    qreal radius = cellSize / 4.0; // raza cercului
    qreal distance = 0.7 * cellSize; // distan?a ?ntre cercuri

    // Ini?ializarea dimensiunilor ?i coordonatelor scenei
    qreal sceneWidth = boardSize * distance;
    qreal sceneHeight = boardSize * distance;
    qreal xOffset = -sceneWidth / 2.0;
    qreal yOffset = -sceneHeight / 2.0;

    qreal buttonX = xOffset + (sceneWidth - buttonWidth) / 2.0;
    qreal buttonY = yOffset + sceneHeight + 10;
    nextPlayerButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
    nextPlayerButton->setEnabled(false);
   
    // Adaug? numele juc?torului 1 la stânga tablei de joc
    player1TextItem = new QGraphicsTextItem(player1Name);
    player1TextItem->setFont(QFont("Impact", 15));  // Seteaz? fontul ?i dimensiunea
    player1TextItem->setDefaultTextColor(player1Color);  // Seteaz? culoarea textului
    player1TextItem->setPos(xOffset - 100, yOffset + sceneHeight / 2 - player1TextItem->boundingRect().height() / 2);
    applyGlowEffect(player1TextItem, 10, player1Color, 0);
    addItem(player1TextItem);

    // Adaug? numele juc?torului 2 la dreapta tablei de joc
    player2TextItem = new QGraphicsTextItem(player2Name);
    player2TextItem->setFont(QFont("Impact", 15));  // Seteaz? fontul ?i dimensiunea
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
            circlesList.append(circle);
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
void GameScene::saveButtonClicked()
{
    emit isPiecePlaced(piecePlaced);
}
void GameScene::switchColor()
{
    if (currentColor == player1Color)
    {
        currentColor = player2Color;
        turnInfo->setPlainText(player2Name+"'s turn!");
        applyGlowEffect(player2TextItem, 20, player2Color, 0);
        player1TextItem->setGraphicsEffect(nullptr);
        
    }
    else
    {
        currentColor = player1Color;
        turnInfo->setPlainText(player1Name+"'s turn!");
        applyGlowEffect(player1TextItem, 20, player1Color, 0);
        player2TextItem->setGraphicsEffect(nullptr);
    }

    nextPlayerButton->setEnabled(false);
    nextPlayerButton->setStyleSheet(BUTTON_DISABLED_STYLE);
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
void GameScene::onBoardLoaded(Board loadedBoard,int isLastPiecePlaced)
{
    clear();
    circlesList.clear();
    lines.clear();
    if (nextPlayerButton==nullptr) {
        nextPlayerButton = new QPushButton("Next Player", nullptr);
    }
    if (isLastPiecePlaced == 1)
    {
        nextPlayerButton->setEnabled(true);
        nextPlayerButton->setStyleSheet(BUTTON_ENABLED_STYLE);
        piecePlaced = true;
    }
    else if(isLastPiecePlaced == 0)
    {
        nextPlayerButton->setEnabled(false);
        nextPlayerButton->setStyleSheet(BUTTON_DISABLED_STYLE);
        piecePlaced = false;
    }

    //connect(nextPlayerButton, &QPushButton::clicked, this, &GameScene::switchColor);
    qreal buttonWidth = Width * 0.15;     // 15% din l??imea scenei
    qreal buttonHeight = Height * 0.07;; // 5% din ?n?l?imea scenei
  

    qreal radius = cellSize / 4.0; // raza cercului
    qreal distance = 0.7 * cellSize; // distan?a ?ntre cercuri

    // Ini?ializarea dimensiunilor ?i coordonatelor scenei
    qreal sceneWidth = loadedBoard.getSize()* distance;
    qreal sceneHeight = loadedBoard.getSize()* distance;
    qreal xOffset = -sceneWidth / 2.0;
    qreal yOffset = -sceneHeight / 2.0;

    qreal buttonX = xOffset + (sceneWidth - buttonWidth) / 2.0;
    qreal buttonY = yOffset + sceneHeight + 10;
    nextPlayerButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Adaug? numele juc?torului 1 la stânga tablei de joc
    player1TextItem = new QGraphicsTextItem(player1Name);
    player1TextItem->setFont(QFont("Arial", 12));  // Seteaz? fontul ?i dimensiunea
    player1TextItem->setDefaultTextColor(player1Color);  // Seteaz? culoarea textului
    player1TextItem->setPos(xOffset - 150, yOffset + sceneHeight / 2 - player1TextItem->boundingRect().height() / 2);
   // player1TextItem->setGraphicsEffect(glowEffect);
    addItem(player1TextItem);

    // Adaug? numele juc?torului 2 la dreapta tablei de joc
    player2TextItem = new QGraphicsTextItem(player2Name);
    player2TextItem->setFont(QFont("Arial", 12));  // Seteaz? fontul ?i dimensiunea
    player2TextItem->setDefaultTextColor(player2Color);  // Seteaz? culoarea textului
    player2TextItem->setPos(xOffset + sceneWidth + 50, yOffset + sceneHeight / 2 - player2TextItem->boundingRect().height() / 2);
    addItem(player2TextItem);

    //Adaug? numele juc?torului curent deasupra tablei de joc
    turnInfo = new QGraphicsTextItem(player1Name + "'s turn");
    turnInfo->setFont(QFont("Arial", 14));  // Seteaz? fontul ?i dimensiunea
    turnInfo->setDefaultTextColor(Qt::lightGray);  // Seteaz? culoarea textului
    turnInfo->setPos(xOffset + sceneWidth / 2 - turnInfo->boundingRect().width() / 2, yOffset - 50);  // Ajusteaz? pozi?ia pentru a fi deasupra ?i la mijlocul tablei
    addItem(turnInfo);

    setSceneRect(xOffset, yOffset, sceneWidth, sceneHeight);
    for (qreal i = 0; i < loadedBoard.getSize(); ++i)
    {
        for (qreal j = 0; j < loadedBoard.getSize(); ++j)
        {
            QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(i * distance + xOffset, j * distance + yOffset, radius, radius);
            circle->setPen(QPen(Qt::black));
             QColor cellColor = loadedBoard(j,i).getColor();
            circle->setBrush(QBrush(cellColor));
            circle->setFlag(QGraphicsItem::ItemIsSelectable);
            circle->setData(0, i);  // ?n prima valoare (index 0), stocheaz? i
            circle->setData(1, j);  // ?n a doua valoare (index 1), stocheaz? j
            circle->setData(2, QBrush(cellColor)); //In a treia valoarea stocheaza culoarea
            circlesList.append(circle);
            addItem(circle);
        }
    }
    for (const auto& bridge : loadedBoard.getBridges())
    {
        // Ob?ine?i coordonatele (i, j) ale celor dou? cercuri conectate de pod
        uint16_t j1 = bridge.getPiece1().getX();
        uint16_t i1 = bridge.getPiece1().getY();
        uint16_t j2 = bridge.getPiece2().getX();
        uint16_t i2 = bridge.getPiece2().getY();

        // Ad?uga?i o linie între cele dou? cercuri
        QGraphicsLineItem* line = new QGraphicsLineItem();
        // Seteaz? culoarea în func?ie de ce condi?ie consideri necesar?
        QPen pen(bridge.getPiece1().getColor(), 2, Qt::SolidLine);
        line->setPen(pen);
        line->setLine(xOffset + i1 * distance + radius / 2, yOffset + j1 * distance + radius / 2,
            xOffset + i2 * distance + radius / 2, yOffset + j2 * distance + radius / 2);
        addItem(line);
        lines.append(line);
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
void GameScene::onMineExploded(Board board)
{
    if (nextPlayerButton != nullptr)
    {
        nextPlayerButton->setEnabled(true);
        nextPlayerButton->setStyleSheet(BUTTON_ENABLED_STYLE);
        piecePlaced = true;
    }

    // Itrează prin lista de cercuri
    foreach(QGraphicsEllipseItem * circle, circlesList)
    {
        // Obține coordonatele cercului din datele sale
        int i = circle->data(1).toInt();
        int j = circle->data(0).toInt();
        if (i == board.dozer.first && j == board.dozer.second)
            circle->setBrush(QBrush(Qt::blue));
        else
        { // Actualizează datele cercului cu cele din noua placă (board)
            QColor cellColor = board(i, j).getColor();
            circle->setBrush(QBrush(cellColor));
            circle->setData(2, QBrush(cellColor));
        }
        if (i > 0 && i < board.board.size() && j>0 && j < board.board.size())
        {
            for (QGraphicsItem* bridgeItem : items()) {
                if (bridgeItem->type() == QGraphicsLineItem::Type) {
                    QGraphicsLineItem* line = qgraphicsitem_cast<QGraphicsLineItem*>(bridgeItem);
                    int lineX1 = line->data(0).toUInt();
                    int lineY1 = line->data(1).toUInt();
                    int lineX2 = line->data(2).toUInt();
                    int lineY2 = line->data(3).toUInt();

                    if ((lineY1 == i && lineX1 == j) || (lineY2 == i && lineX2 == j)) {
                        emit deleteBridgeClicked(lineX1, lineY1, lineX2, lineY2);
                        removeItem(line);
                    }
                }
            }
        }
    }
    qreal radius = cellSize / 4.0;
    qreal distance = 0.7 * cellSize;
    qreal sceneWidth = boardSize * distance;
    qreal sceneHeight = boardSize * distance;
    qreal xOffset = -sceneWidth / 2.0;
    qreal yOffset = -sceneHeight / 2.0;

    for (const auto& bridge : board.getBridges())
    {
        uint16_t j1 = bridge.getPiece1().getX();
        uint16_t i1 = bridge.getPiece1().getY();
        uint16_t j2 = bridge.getPiece2().getX();
        uint16_t i2 = bridge.getPiece2().getY();
        QGraphicsLineItem* line = new QGraphicsLineItem();
        QPen pen(bridge.getPiece1().getColor(), 2, Qt::SolidLine);
        line->setPen(pen);
        line->setLine(xOffset + i1 * distance + radius / 2, yOffset + j1 * distance + radius / 2, xOffset + i2 * distance + radius / 2, yOffset + j2 * distance + radius / 2);
        line->setData(0, j1);
        line->setData(1, i1);
        line->setData(2, j2);
        line->setData(3, i2);
        addItem(line);
        lines.append(line);
    }

}
void GameScene::randomPiece(uint16_t X,uint16_t Y)
{

    if (X_before != -1 && Y_before != -1)
    {
        for (QGraphicsItem* item : items()) {
            if (item->type() == QGraphicsEllipseItem::Type) {
                QGraphicsEllipseItem* ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
                int itemX = ellipse->data(0).toInt();
                int itemY = ellipse->data(1).toInt();
                if (X_before == itemX && Y_before == itemY) {
                    ellipse->setBrush(QBrush(Qt::gray));
                    ellipse->setData(2, QBrush(Qt::gray)); // Actualizează culoarea dată pentru utilizarea ulterioară
                    break;
                }
            }
        }
    }

    for (QGraphicsItem* item : items()) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            QGraphicsEllipseItem* ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            int itemX = ellipse->data(0).toInt();
            int itemY = ellipse->data(1).toInt();
            X_before = itemX;
            Y_before = itemY;
            if (itemX == X && itemY == Y) {
                ellipse->setBrush(QBrush(Qt::blue));
                ellipse->setData(2, QBrush(Qt::blue)); // Actualizează culoarea dată pentru utilizarea ulterioară
                for (QGraphicsItem* bridgeItem : items()) {
                    if (bridgeItem->type() == QGraphicsLineItem::Type) {
                        QGraphicsLineItem* line = qgraphicsitem_cast<QGraphicsLineItem*>(bridgeItem);
                        int lineX1 = line->data(0).toUInt();
                        int lineY1 = line->data(1).toUInt();
                        int lineX2 = line->data(2).toUInt();
                        int lineY2 = line->data(3).toUInt();

                        if ((lineY1 == itemX && lineX1 == itemY) || (lineY2 == itemX && lineX2 == itemY)) {
                            emit deleteBridgeClicked(lineX1, lineY1, lineX2, lineY2);
                            removeItem(line);
                        }
                    }
                }
                break;
            }
        }
    }
}

void GameScene::gameFinished()
{
    if (currentColor == player1Color)
    {
        turnInfo->setPlainText(player1Name + " won!");
    }
    else if(currentColor == player1Color)
    {
        turnInfo->setPlainText(player2Name + " won!");
    }
}