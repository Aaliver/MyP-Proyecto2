import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

Dialog {
    id: editDialog
    width: window.width / 2.5
    height: window.height / 2
    title: "Editar Rola"

    modal: true
    anchors.centerIn: Overlay.overlay
    standardButtons: Dialog.Save | Dialog.Cancel

    property var editData: null
    property var fields: []

    property int edit: EditDialog.Edit.Default
    enum Edit {
        Rola,
        Album,
        Artist,
        Default
    }

    signal saveData(int editType, var values)

    Loader {
        anchors.fill: parent
        active: editDialog.visible
        sourceComponent: component
    }

    Component {
        id: component
        ListView {
            id: dataView
            anchors.fill: parent
            spacing: 5
            clip: true

            model: editDialog.fields

            delegate: Rectangle {
                height: 45
                width: parent.width
                color: palette.midlight
                radius: 5

                RowLayout {
                    id: row
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 15
                    spacing: 15

                    property bool editing: false
                    property string editValue: editDialog.editData != null ?
                        editDialog.editData[modelData.display] : ""

                    Text {
                        text: modelData.name + ":"
                        color: edit.Material.accent
                        font.bold: true
                    }

                    Text {
                        id: textView
                        text: row.editValue
                        Layout.leftMargin: 16
                        color: palette.text
                        visible: !row.editing
                    }

                    TextField {
                        id: textEdit
                        Layout.preferredWidth: 150
                        Layout.fillHeight: parent.height

                        text: row.editValue
                        color: "#d0d0d0"
                        visible: row.editing

                        background: Rectangle {
                            color: palette.midlight
                        }

                        onTextEdited: {
                            editDialog.editData[modelData.display] = text
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Boton {
                        id: edit
                        Layout.preferredWidth: 40
                        Layout.preferredHeight: 40
                        iconSource: "qrc:/img/images/pen.svg"

                        onClicked: {
                            textEdit.forceActiveFocus()
                            row.editing = true
                        }
                    }
                }
            }
        }
    }

    onAccepted: {
        saveData(edit, editData)
    }
}
