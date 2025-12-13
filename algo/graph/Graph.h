#pragma once

#include <cstdint>
#include <istream>
#include <ostream>
#include <regex>
#include <string>
#include <unordered_map>

namespace Ps::Algo {

constexpr char kSeparator = '\t';

using vertexid_t = uint32_t;
using edgeid_t = uint64_t;

/// @brief Heap indexing function object used for Dijkstra shortest path, Prim's minimum spanning tree
template <typename VertexType>
struct HeapIndex
{
    HeapIndex(std::unordered_map<vertexid_t, size_t>& map)
        : map_{map}
    {}
    void operator()(VertexType* vertex, size_t i) { map_[vertex->id()] = i; }

    std::unordered_map<vertexid_t, size_t>& map_;
};

/// @brief Vertex class abstracts Graph vertex. Edges list structure is left to derived
///        class to define as it is well informed to make which kind will suit for the need.
class Vertex
{
public:
    Vertex(vertexid_t id)
        : id_{id}
    {}
    virtual ~Vertex() = default;

    virtual std::string to_string() const { return std::to_string(id_); }

    vertexid_t id() const { return id_; }
    void set_id(vertexid_t id) { id_ = id; }

private:
    vertexid_t id_;
};

/// @brief Simple Edge class (u, v) that does not need other attributes
///        except that id and vertices.
template <typename VertexType>
class Edge
{
public:
    Edge(edgeid_t id, VertexType* u, VertexType* v)
        : id_{id}
        , u_{u}
        , v_{v}
    {}
    ~Edge() = default;

    edgeid_t id() const { return id_; }
    VertexType* u() const { return u_; }
    VertexType* v() const { return v_; }

    void set_id(edgeid_t id) { id_ = id; }
    void set_u(VertexType* u) { u_ = u; }
    void set_v(VertexType* v) { v_ = v; }

private:
    edgeid_t id_;
    VertexType* u_;
    VertexType* v_;
};

/// @brief Graph class that abstract common behaviors for a graph.
template <typename VertexType, typename EdgeType>
class Graph
{
public:
    enum class Type
    {
        Directed,
        Undirected
    };

public:
    Graph() = default;
    virtual ~Graph() = default;

    Type type() const { return type_; }
    virtual vertexid_t vertices_size() const = 0;
    virtual edgeid_t edges_size() const = 0;
    virtual VertexType* get_vertex(vertexid_t id) const = 0;
    virtual EdgeType* get_edge(edgeid_t id) const = 0;

    void set_type(Type type) { type_ = type; }
    virtual void add_vertex(vertexid_t id) = 0;
    virtual edgeid_t add_edge(edgeid_t id, VertexType* u, VertexType* v, int32_t value) = 0;

    void read_adjacency_list(std::istream& input_stream);
    void write_adjacency_list(std::ostream& output_stream);

protected:
    virtual void reserve_vertices(vertexid_t num_vertices) = 0;
    virtual void reserve_edges(edgeid_t num_edges) = 0;

    void read_edges(std::istream& input_stream);

private:
    Type type_;
};

// Implementation

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::read_adjacency_list(std::istream& input_stream)
{
    std::string buf;

    std::getline(input_stream, buf); // Read type: "directed" or "undirected"
    if (buf == "directed") {
        type_ = Type::Directed;
    }
    else if (buf == "undirected") {
        type_ = Type::Undirected;
    }
    else {
        throw std::runtime_error{"Graph format error! Unknown type, expected 'directed or undirected'"};
    }

    std::getline(input_stream, buf); // Read line that has number of vertices and edges.

    std::smatch results;
    if (!std::regex_search(buf, results, std::regex{R"(^(\d+)(\s+\d+)?)"})) {
        throw std::runtime_error{"Graph format error! Number of nodes followed by optional number of edges not found."};
    }

    auto num_vertices = static_cast<vertexid_t>(std::stoi(results[1]));
    reserve_vertices(num_vertices);
    if (results[2].matched) {
        auto num_edges = static_cast<edgeid_t>(std::stol(results[2]));
        reserve_edges(num_edges);
    }

    // Create all vertices and add to graph
    for (vertexid_t i = 0; i < num_vertices; ++i) {
        add_vertex(i);
    }

    read_edges(input_stream);
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::write_adjacency_list(std::ostream& output_stream)
{
    if (type() == Type::Directed) {
        output_stream << "directed\n";
    }
    else {
        output_stream << "undirected\n";
    }

    const auto n = vertices_size();
    output_stream << n << kSeparator << edges_size() << "\n\n";

    for (vertexid_t id = 0; id < n; ++id) {
        const auto& vertex = get_vertex(id);
        output_stream << vertex->to_string() << '\n';
    }
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::read_edges(std::istream& input_stream)
{
    auto pattern = std::regex{R"(\s+)"};

    edgeid_t edge_id = 0;
    edgeid_t prev_edge_id;
    int value;

    std::string buf;
    while (!input_stream.eof()) {
        std::getline(input_stream, buf);
        if (buf.empty()) {
            continue;
        }

        auto it = std::sregex_token_iterator{buf.begin(), buf.end(), pattern, -1};
        const std::sregex_token_iterator end_it{};

        auto id = static_cast<vertexid_t>(std::stoi(it->str()));
        auto u = get_vertex(id);

        std::string str;
        for (++it; it != end_it; ++it) {
            str = it->str();

            const auto i = str.find(",");
            if (i != std::string::npos) {
                id = static_cast<vertexid_t>(std::stoi(str.substr(0, i)));
                value = std::stoi(str.substr(i + 1));
            }
            else {
                id = static_cast<vertexid_t>(std::stoi(it->str()));
                value = 0;
            }

            auto v = get_vertex(id);

            prev_edge_id = edge_id;
            edge_id = add_edge(edge_id, u, v, value);
            if (prev_edge_id >= edge_id) {
                throw std::logic_error{"prev_edge_id >= edge_id"};
            }
        }
    }
}

} // namespace Ps::Algo
