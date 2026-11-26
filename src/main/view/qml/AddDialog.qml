import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

Dialog {
    id: addDialog
    width: window.width / 3
    height: window.height / 2
    title: "Añadir Artista"

    modal: true
    anchors.centerIn: Overlay.overlay
    standardButtons: Dialog.Save | Dialog.Cancel

    property int type: AddDialog.Add.Person
    readonly property var addNames: ["Persona", "Grupo"]
    enum Add {
        Person,
        Group
    }

    property var add: ({})
    signal addData(int editType, var values)

    contentItem: ColumnLayout {
        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            spacing: 10

            Repeater {
                model: addDialog.addNames

                delegate: Boton {
                    Layout.fillWidth: true
                    text: modelData
                    font.pixelSize: 15
                    highlighted: addDialog.type === index
                    onClicked: {
                        addDialog.add = ({})
                        addDialog.type = index
                    }

                    required property int index
                    required property string modelData
                }
            }
        }

        Loader {
            id: dataLoader
            Layout.fillWidth: true
            Layout.fillHeight: true
            active: addDialog.visible
            sourceComponent: component
        }
    }

    ListModel {
        id: addPersonModel
        ListElement { name: "Nombre artístico"; field: "stage_name" }
        ListElement { name: "Nombre real"; field: "real_name" }
        ListElement { name: "Fecha de nacimiento"; field: "birth_date" }
        ListElement { name: "Fecha de muerte"; field: "death_date" }
    }

    ListModel {
        id: addGroupModel
        ListElement { name: "Nombre"; field: "name" }
        ListElement { name: "Fecha de inicio"; field: "birth_date" }
        ListElement { name: "Fecha de finalización"; field: "death_date" }
    }

    Component {
        id: component

        ListView {
            anchors.fill: parent
            spacing: 5
            clip: true

            model: addDialog.type === AddDialog.Add.Person ?
                addPersonModel : addGroupModel

            delegate: Rectangle {
                id: listViewDelegate
                height: 50
                width: parent.width
                color: palette.midlight
                border.width: 0
                border.color: Material.accent
                radius: 5

                RowLayout {
                    height: parent.height - 5
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 5

                    TextField {
                        Layout.fillWidth: true
                        Layout.preferredHeight: listViewDelegate.height - 20
                        Layout.alignment: text.trim() != "" || activeFocus ?
                            Qt.AlignBottom : Qt.AlignVCenter

                        placeholderText: model.name
                        font.pixelSize: 15
                        color: palette.text

                        background: Rectangle {
                            color: palette.midlight
                        }

                        onActiveFocusChanged: {
                            listViewDelegate.border.width = activeFocus ? 2 : 0
                        }

                        onTextEdited: {
                            addDialog.add[model.field] = text
                        }
                    }
                }
            }
        }
    }

    onAccepted: {
        let values = {}
        let model = dataLoader.item.model
        for (let i = 0; i < model.count; ++i) {
            let element = model.get(i)
            values[element.field] = (element.field in addDialog.add) ?
                addDialog.add[element.field] : ""
        }
        addData(type, values)
    }
}
