#pragma once
#pragma once
#include <iostream>
#include "GraphNode.h"
#include "Queue.h"
#include "Stack.h"
using std::cout; using std::endl;

template <class T>
class Graph {
    typedef GraphNode<T> NG;
public:
    Queue<NG*> qv;
    NG* padre = nullptr;
    Graph() {}
    Graph(T data) {
        if (!padre) {
            padre = new NG(data);
        }
    }

    void addEdge(T dataParend, T data, int cost) {
        NG* tmp = DSearch(dataParend);
        if (tmp != nullptr && dataParend != data) {
            if (DSearch(data) == nullptr) {
                tmp->adyacentes.push_back(new NG(data));
                tmp->costoAdyacentes.push_back(cost);
            }
            else if (searchPadre(tmp, data) == nullptr) {
                tmp->adyacentes.push_back(DSearch(data));
                tmp->costoAdyacentes.push_back(cost);
            }
            NG* tmpD = DSearch(data);
            tmpD->adyacentes.push_back(tmp);
            tmpD->costoAdyacentes.push_back(cost);
        }
    }

    NG* search(T data) {
        Queue<NG*> qs;
        NG* tmp = padre;
        while (tmp) {
            qv.push(tmp);
            if (tmp->getData() == data) {
                resetVisitados();
                return tmp;
                break;
            }
            else if (tmp->visitado != true) {
                tmp->visitado = true;
                for (int i = 0; i < tmp->adyacentes.Size(); i++) {
                    qs.push(tmp->adyacentes.at(i));
                    qv.push(tmp->adyacentes.at(i));
                }
            }
            if (qs.root == nullptr) {
                resetVisitados();
                return nullptr;
                break;
            }
            tmp = qs.root->dato;
            qs.pop();
        }
        return nullptr;
    }

	NG* WSearchLimit(T data) {
		Queue<NG*> qs;
		NG* tmp = padre;
		int attempts = 0;
		while (tmp && attempts < 10) {
			qv.push(tmp);
			if (tmp->getData() == data) {
				resetVisitados();
                std::cout << "found" << std::endl;
				return tmp;
				break;
			}
			else if (tmp->visitado != true) {
				tmp->visitado = true;
				attempts++;
				for (int i = 0; i < tmp->adyacentes.size(); i++) {
					qs.push(tmp->adyacentes.at(i));
					qv.push(tmp->adyacentes.at(i));
				}
			}
			if (qs.root == nullptr) {
				resetVisitados();
				return nullptr;
				break;
			}
			tmp = qs.root->dato;
			qs.pop();
		}
        if (attempts >= 10) {
            
            std::cout << "attemps exceeded" << std::endl;
        }
		return nullptr;
	}

    NG* DSearch(T data) {
        Stack<NG*> ss;
        NG* tmp = padre;
        ss.push(tmp);
        while (tmp) {
            //cout << tmp->visitado << endl;
            if (tmp->getData() == data) {
                resetVisitados();
                return tmp;
                break;
            }
            else if (tmp->visitado != true) {
                tmp->visitado = true;
                qv.push(tmp);
                ss.pop();
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    if (tmp->adyacentes.at(i)->visitado != true) {
                        ss.push(tmp->adyacentes.at(i));
                    }
                }
            }
            else {
                ss.pop();
            }
            if (ss.last == nullptr) {
                resetVisitados();
                //cout << "nop" << endl;
                return nullptr;
                break;
            }
            tmp = ss.last->value;
        }
        resetVisitados();
        return nullptr;
    }

    NG* searchPadre(NG* head, T data) {
        NG* tmp = head;
        while (tmp) {
            qv.push(tmp);
            if (tmp->visitado == false) {
                tmp->visitado = true;
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    tmp->adyacentes.at(i)->visitado = true;
                    qv.push(tmp->adyacentes.at(i));
                    if (tmp->adyacentes.at(i)->getData() == data) {
                        resetVisitados();
                        tmp = tmp->adyacentes.at(i);
                        return tmp;
                        break;
                    }
                }
                resetVisitados();
                return nullptr;
                break;
            }
        }
        return nullptr;
    }

    void printBFS() {
        Queue<NG*> qs;
        NG* tmp = padre;
        //resetVisitados();
        while (tmp) {
            qv.push(tmp);
            if (tmp->visitado != true) {
                tmp->visitado = true;
                cout << tmp->getData() << endl;
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    qs.push(tmp->adyacentes.at(i));
                    qv.push(tmp->adyacentes.at(i));
                }
            }
            if (qs.first == nullptr) {
                resetVisitados();
                break;
            }
            tmp = qs.first->value;
            qs.pop();
        }
    }

    void Dijkstra(NG* start, NG* end) {

    }

    void resetVisitados() {
        while (qv.size() > 0) {
            qv.first->value->visitado = false;
            qv.pop();
        }
    }
};