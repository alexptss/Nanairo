/*!
  \file NMaterialModel.qml
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

import QtQuick 2.6
import QtQuick.Controls 1.5

QtObject {
  id: material_model

  property var model: ListModel {
  }

  function addMaterialElement(element) {
    console.assert(element != null, "Element is null.");
    model.append(element);
  }

  function createGeneralElement() {
    var element = {};
    return element;
  }

  function isValidIndex(index) {
    var isValid = (0 <= index) && (index < model.count);
    return isValid;
  }

  function getMaterialElement(index) {
    console.assert(isValidIndex(index), "Material index is out of range: ", index);
    return model.get(index);
  }
}
