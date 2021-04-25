#pragma once
#include <QtWidgets/QWidget>
#include "ui_Result.h"

class ResultWidget : public QWidget
{
	Q_OBJECT

public:
	ResultWidget(QWidget *parent = Q_NULLPTR);

private:
	Ui::resultWidget ui;
};