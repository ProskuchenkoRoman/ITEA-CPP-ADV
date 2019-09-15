#pragma once

#include <QtWidgets>

#include "PalindromeResolver.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    QMenuBar* menuBar;
    QMenu* menuFile;

    QLabel* nonPalindromesLabel;
    QLabel* palindromesLabel;

    QListWidget* nonPalindromes;
    QListWidget* palindromes;

    QStatusBar* statusBar;

    void addNonPalindromes(const ITEA::Coach::L2::PalindromeResolver::PalindromeResults& results);
    void addPalindromes(const ITEA::Coach::L2::PalindromeResolver::PalindromeResults& results);
    void addingResults(const ITEA::Coach::L2::PalindromeResolver::Words& words, QListWidget* listWidget);
};
