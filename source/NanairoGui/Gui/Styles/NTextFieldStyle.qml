/*!
  \file NTextFieldStyle.qml
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import "../nanairo.js" as Nanairo

TextFieldStyle {
  background: Rectangle {
    color: "white"
    border.color: Qt.darker(color, Nanairo.defaultDarkerScale)
    border.width: 1
  }
}
