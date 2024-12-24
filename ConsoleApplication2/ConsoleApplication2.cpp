#include <iostream>
#include <vector>
#include <string>
#include <memory>

class TaskModel {
private:
    std::vector<std::string> tasks;
public:
    void addTask(const std::string& task) {
        tasks.push_back(task);
    }

    void removeTask(size_t index) {
        if (index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    const std::vector<std::string>& getTasks() const {
        return tasks;
    }
};

class TaskView {
public:
    void displayTasks(const std::vector<std::string>& tasks) {
        std::cout << "Your tasks:" << std::endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i] << std::endl;
        }
        if (tasks.empty()) {
            std::cout << "No tasks found." << std::endl;
        }
    }

    void showMessage(const std::string& message) {
        std::cout << message << std::endl;
    }
};

class TaskController {
private:
    std::shared_ptr<TaskModel> model;
    std::shared_ptr<TaskView> view;
public:
    TaskController(const std::shared_ptr<TaskModel>& m, const std::shared_ptr<TaskView>& v)
        : model(m), view(v) {}

    void addTask(const std::string& task) {
        model->addTask(task);
        view->showMessage("Task added successfully.");
    }

    void removeTask(size_t index) {
        if (index <= model->getTasks().size() && index > 0) {
            model->removeTask(index - 1);
            view->showMessage("Task removed successfully.");
        }
        else {
            view->showMessage("Invalid task index.");
        }
    }

    void showTasks() {
        view->displayTasks(model->getTasks());
    }
};

int main() {
    auto model = std::make_shared<TaskModel>();
    auto view = std::make_shared<TaskView>();
    TaskController controller(model, view);

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Remove Task\n";
        std::cout << "3. Show Tasks\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(); // Очищаємо буфер
        if (choice == 1) {
            std::string task;
            std::cout << "Enter task: ";
            std::getline(std::cin, task);
            controller.addTask(task);
        }
        else if (choice == 2) {
            size_t index;
            std::cout << "Enter task index to remove: ";
            std::cin >> index;
            controller.removeTask(index);
        }
        else if (choice == 3) {
            controller.showTasks();
        }
    } while (choice != 0);

    return 0;
}
