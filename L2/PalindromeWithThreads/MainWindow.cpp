#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , menuBar{new QMenuBar}
    , menuFile{new QMenu{"&File"}}
    , nonPalindromesLabel{new QLabel{"Non palindromes"}}
    , palindromesLabel{new QLabel{"Palindromes"}}
    , nonPalindromes{new QListWidget}
    , palindromes{new QListWidget}
    , statusBar{new QStatusBar}
{
    menuFile->addAction("&Open",
        this, [this]()
        {
            const QString fileWithPalindromes{QFileDialog::getOpenFileName(this,
                                                                           "Open file with palindormes",
                                                                           QString(),
                                                                           "Text files (*.txt);;All files (*.*)")};
            if(!fileWithPalindromes.isEmpty())
            {
                QFile file{fileWithPalindromes};
                if(file.open(QIODevice::ReadOnly))
                {
                    nonPalindromes->clear();

                    ITEA::Coach::L2::PalindromeResolver::Words words;

                    QTextStream stream{&file};
                    while(!stream.atEnd())
                    {
                        QString word;
                        stream >> word;
                        words.push_back(word.toStdU32String());
                    }

                    const ITEA::Coach::L2::PalindromeResolver::PalindromeResults& results{ITEA::Coach::L2::PalindromeResolver::resolve(words)};

                    addNonPalindromes(results);
                    addPalindromes(results);
                }
            }
        }, Qt::CTRL + Qt::Key_O);
    menuFile->addSeparator();
    menuFile->addAction("E&xit", qApp, &QApplication::quit, Qt::CTRL + Qt::Key_X);

    menuBar->addMenu(menuFile);

    QVBoxLayout* vNonPalindromes{new QVBoxLayout};
    vNonPalindromes->setSpacing(5);
    vNonPalindromes->setMargin(0);
    vNonPalindromes->addWidget(nonPalindromesLabel, 0, Qt::AlignCenter);
    vNonPalindromes->addWidget(nonPalindromes);

    QWidget* nonPalindromesWidget{new QWidget};
    nonPalindromesWidget->setLayout(vNonPalindromes);

    QVBoxLayout* vPalindromes{new QVBoxLayout};
    vPalindromes->setSpacing(5);
    vPalindromes->setMargin(0);
    vPalindromes->addWidget(palindromesLabel, 0, Qt::AlignCenter);
    vPalindromes->addWidget(palindromes);

    QWidget* palindromesWidget{new QWidget};
    palindromesWidget->setLayout(vPalindromes);

    QSplitter* splitter{new QSplitter{Qt::Horizontal}};
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->addWidget(nonPalindromesWidget);
    splitter->addWidget(palindromesWidget);

    QGridLayout* grid{new QGridLayout(this)};
    grid->setSpacing(5);
    grid->setMargin(0);
    grid->addWidget(menuBar, 0, 0, 1, 2);
    grid->addWidget(splitter, 1, 0, 1, 2);
    grid->addWidget(statusBar, 3, 0, 1, 2);
}

void MainWindow::addNonPalindromes(const ITEA::Coach::L2::PalindromeResolver::PalindromeResults& results)
{
    const ITEA::Coach::L2::PalindromeResolver::NonPalindormeStrings& nonPalindromes{std::get<0>(results)};
    addingResults(nonPalindromes, this->nonPalindromes);
}

void MainWindow::addPalindromes(const ITEA::Coach::L2::PalindromeResolver::PalindromeResults& results)
{
    const ITEA::Coach::L2::PalindromeResolver::PalindormeStrings& palindromes{std::get<1>(results)};
    addingResults(palindromes, this->palindromes);
}

void MainWindow::addingResults(const ITEA::Coach::L2::PalindromeResolver::Words &words, QListWidget* listWidget)
{
    for(const ITEA::Coach::L2::PalindromeResolver::Word& word: words)
    {
        listWidget->addItem(QString::fromStdU32String(word));
    }
}
