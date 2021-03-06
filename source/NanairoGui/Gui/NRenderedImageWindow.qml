/*!
  \file NRenderedImageWindow.qml
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Window 2.2
import "RenderedImageWindowItems"

Window {
  id: rendered_image_window

  readonly property int infoViewAreaHeight: 16
  readonly property int textFontSize: 10
  readonly property int windowWidth: imageWidth
  readonly property int windowHeight: imageHeight + infoViewAreaHeight
  property int imageWidth
  property int imageHeight
  property bool isPreviewMode: false

  width: windowWidth
  height: windowHeight

  maximumWidth: windowWidth
  maximumHeight: windowHeight
  minimumWidth: windowWidth
  minimumHeight: windowHeight

  Rectangle {
    id: view_area
    anchors.fill: parent 
    color: rendered_image_window.color

    Rectangle {
      id: rendering_info_view_area
      width: rendered_image_window.windowWidth
      height: rendered_image_window.infoViewAreaHeight
      color: view_area.color

      NText {
        id: fps_label
        x: 4
        y: 0
        height: rendered_image_window.infoViewAreaHeight
        text: qsTr("FPS: ")
      }

      NText {
        id: fps_value_text
        x: fps_label.x + fps_label.width
        y: 0
        height: rendered_image_window.infoViewAreaHeight
        text: "00.00"
      }

      NText {
        id: cycle_label
        x: (fps_label.x + fps_label.width) + 45
        y: 0
        height: rendered_image_window.infoViewAreaHeight
        text: qsTr("Cycle: ")
      }

      NText {
        id: cycle_value_text
        x: cycle_label.x + cycle_label.width
        y: 0
        height: rendered_image_window.infoViewAreaHeight
        text: "00000000"
      }

      NText {
        id: time_label
        x: (cycle_label.x + cycle_label.width) + 70
        y: 0
        height: rendered_image_window.infoViewAreaHeight
        text: qsTr("Time: ")
      }

      NText {
        id: time_value_text
        x: time_label.x + time_label.width
        y: 0
        height: rendered_image_window.infoViewAreaHeight
        text: "00 h 00 m 00.000 s"
      }
    }

    Rectangle {
      id: rendered_image_view_area
      y: (rendering_info_view_area.y + rendering_info_view_area.height)
      width: rendered_image_window.imageWidth
      height: rendered_image_window.imageHeight
      color: view_area.color

      Image {
        id: rendered_image_view
        anchors.fill: parent
        cache: false

        function updateRenderedImage(fps, cycle, time) {
          source = "image://renderedImage/preview" + cycle;
          fps_value_text.text = fps;
          cycle_value_text.text = cycle;
          time_value_text.text = time;
        }

        NPreviewEventArea {
          id: preview_event_area
          anchors.fill: parent
          enabled: rendered_image_window.isPreviewMode
        }
      }
    }
  }

  onClosing: nanairoManager.stopping()

  Connections {
    target: nanairoManager
    onUpdated: rendered_image_view.updateRenderedImage(fps, cycle, time)
    onFinished: close()
  }
}
