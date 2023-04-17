import SwiftUI

let didIPrefix = "DidI_"

var actions: [String: Date] = [:]

func saveAction(action: String) {
    actions[didIPrefix + action] = Date()
    UserDefaults.standard.set(actions, forKey: "actions")
}

func deleteAction(action: String) {
    actions.removeValue(forKey: didIPrefix + action)
    UserDefaults.standard.set(actions, forKey: "actions")
}

func deleteAllActions() {
    actions.removeAll()
    UserDefaults.standard.set(actions, forKey: "actions")
}

func loadActions() {
    if let savedActions = UserDefaults.standard.dictionary(forKey: "actions") as? [String: Date] {
        actions = savedActions
    }
}

struct ContentView: View {
    @State private var selectedAction: String = ""
    @State private var actionOptions: [String] = ["Select an action...", "Lock the car", "Close the house", "Turn off the lights", "Turn off the thermostat", "Say hi to Craig"]
    @State private var newAction: String = ""

    var body: some View {
        VStack {
            Text("Did I...?")
                .font(.largeTitle)
                .padding()
            
            Picker(selection: $selectedAction, label: Text("What did you do?")) {
                ForEach(actionOptions, id: \.self) { option in
                    Text(option)
                        .disabled(option == "Select an action...")
                }
            }
            .pickerStyle(MenuPickerStyle())
            .padding()
            .onChange(of: selectedAction) { newValue in
                selectedAction = newValue
            }
            
            HStack {
                Button("Save") {
                    if !selectedAction.isEmpty {
                        saveAction(action: selectedAction)
                        selectedAction = ""
                    }
                }
                .padding()
                Button("Delete") {
                    if let index = actionOptions.firstIndex(of: selectedAction) {
                        actionOptions.remove(at: index)
                        UserDefaults.standard.set(actionOptions, forKey: "actionOptions")
                        selectedAction = actionOptions[0]
                    }
                }
                .disabled(selectedAction == "Select an action...")
                .padding()
            }


            HStack {
                TextField("New action", text: $newAction)
                Button("Add") {
                    if !newAction.isEmpty {
                        actionOptions.append(newAction)
                        saveAction(action: newAction)
                        newAction = ""
                        saveActionOptions()
                    }
                }
            }
            .padding()
            
            List {
                ForEach(actions.sorted(by: { $0.key < $1.key }), id: \.key) { keyValue in
                    let key = keyValue.key
                    let value = keyValue.value
                    let dateString = formatDate(value: value)
                    Text("\(String(key.dropFirst(didIPrefix.count))): \(dateString)")
                }
                .onDelete(perform: { indexSet in
                    indexSet.forEach { index in
                        let action = actions.sorted(by: { $0.key < $1.key })[index].key
                        deleteAction(action: String(action.dropFirst(didIPrefix.count)))
                    }
                })
            }
        }
        .onAppear(perform: {
            loadActions()
            loadActionOptions()
        })
    }
    
    private func loadActionOptions() {
        if let savedActionOptions = UserDefaults.standard.array(forKey: "actionOptions") as? [String] {
            actionOptions = savedActionOptions
        }
    }
    
    private func saveActionOptions() {
        UserDefaults.standard.set(actionOptions, forKey: "actionOptions")
    }
    
    private func formatDate(value: Date) -> String {
        let formatter = DateFormatter()
        formatter.dateStyle = .medium
        formatter.timeStyle = .short
        return formatter.string(from: value)
    }
}


struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
