#pragma once

#include <QtWidgets/QWidget>
#include "ui_LifeguardScheduingAutomaticScheduing.h"

class LifeguardScheduingAutomaticScheduing : public QWidget
{
	Q_OBJECT

public:
	LifeguardScheduingAutomaticScheduing(QWidget *parent = Q_NULLPTR);

private:
	Ui::LifeguardScheduingAutomaticScheduingClass ui;
};
