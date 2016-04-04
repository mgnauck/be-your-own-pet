#include "Vertex.h"

Vertex::Vertex() {
}

Vertex::Vertex(Vector const& p) : position(p) {
}

Vertex::Vertex(Vector const& p, Vector const& n) : position(p), normal(n) {
}