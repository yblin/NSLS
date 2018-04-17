//
// Copyright 2014 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_LIST_ADJACENCY_LIST_H_
#define UTIL_LIST_ADJACENCY_LIST_H_

#include <cassert>
#include <vector>

#include "codelibrary/base/macros.h"
#include "codelibrary/util/list/inplace_list.h"
#include "codelibrary/util/pool/object_pool.h"
#include "codelibrary/util/property_map/vector_property_map.h"

namespace cl {

/// Adjacency List.
/**
 * AdjacencyList representation of a graph is a collection of unordered lists,
 * one for each vertex in the graph. Each list describes the set of neighbors of
 * its vertex. For example, the edges (0, 1), (0, 2), (1, 0), (0, 2) will be
 * stored in AdjacencyList as below:
 *    ---      ---      ---
 *   | 0 | -> | 1 | -> | 2 |
 *    ---      ---      ---
 *   | 1 | -> | 0 |
 *    ---      ---
 *   | 2 | -> | 0 |
 *    ---      ---
 */
class AdjacencyList {
    friend class EdgeProperty;

public:
    /// Edge for AdjacencyList.
    class Edge {
        friend class AdjacencyList;
        friend class EdgeMap;

    public:
        Edge()
            : next_(NULL), prev_(NULL), twin_(NULL) {}

        int id()            const { return id_;     }
        int source()        const { return source_; }
        int target()        const { return target_; }

        void set_next(Edge* next) { next_ = next;   }
        const Edge* next()  const { return next_;   }
        Edge* next()              { return next_;   }

        void set_prev(Edge* prev) { prev_ = prev;   }
        const Edge* prev()  const { return prev_;   }
        Edge* prev()              { return prev_;   }

        void set_twin(Edge* twin) { twin_ = twin;   }
        const Edge* twin()  const { return twin_;   }
        Edge* twin()              { return twin_;   }

    private:
        int id_;     // The index of this edge in the AdjacencyList's edges.
        int source_; // The source vertex of edge.
        int target_; // The target vertex of edge.
        Edge* next_; // The pointer to the next edge in the edge list.
        Edge* prev_; // The pointer to the previous edge in the edge list.
        Edge* twin_; // The pointer to the twin edge.
    };

    /// Edge property for AdjacencyList.
    template <typename T>
    class EdgeProperty : public VectorPropertyMap<T> {
        typedef typename std::vector<T>::reference Reference;
        typedef typename std::vector<T>::const_reference ConstReference;

    public:
        EdgeProperty(AdjacencyList* parent, const T& value = T())
            : VectorPropertyMap<T>(parent->size_edges(), value),
              parent_(parent), const_parent_(parent) {
            assert(parent);

            parent->edge_properties_.push_back(this);
        }

        /**
         * Bind the EdgeProperty to const AdjacencyList, in this case, we do not
         * add the edge property into AdjacencyList. It just a static map.
         */
        EdgeProperty(const AdjacencyList* parent, const T& value = T())
            : VectorPropertyMap<T>(parent->size_edges(), value),
              parent_(NULL), const_parent_(parent) {
            assert(parent);
        }

        ~EdgeProperty() {
            if (!parent_) return;

            for (auto i = parent_->edge_properties_.begin();
                 i != parent_->edge_properties_.end(); ++i) {
                if (*i == this) {
                    parent_->edge_properties_.erase(i);
                    break;
                }
            }
        }

        Reference operator[] (const Edge* e) {
            return this->data_[e->id_];
        }

        ConstReference operator[] (const Edge* e) const {
            return this->data_[e->id_];
        }

        Reference operator[] (const Edge& e) {
            return this->data_[e.id_];
        }

        ConstReference operator[] (const Edge& e) const {
            return this->data_[e.id_];
        }

        const AdjacencyList* parent() const { return const_parent_; }

    private:
        AdjacencyList* parent_;             // The pointer to the parent.
        const AdjacencyList* const_parent_; // The const pointer to the parent.

        DISALLOW_COPY_AND_ASSIGN(EdgeProperty);
    };

    typedef InplaceList<Edge> EdgeList;

    explicit AdjacencyList(int size_vertices = 0)
        : size_vertices_(size_vertices),
          size_edges_(0),
          edge_lists_(size_vertices) {
        assert(size_vertices_ >= 0);
    }

    AdjacencyList(const AdjacencyList& adjacency_list) {
        adjacency_list.Clone(this);
    }

    AdjacencyList& operator =(const AdjacencyList& adjacency_list) {
        adjacency_list.Clone(this);
        return *this;
    }

    /**
     * Clear the data and resize the adjacency list.
     */
    void Resize(int size_vertices) {
        assert(size_vertices >= 0);

        clear();
        size_vertices_ = size_vertices;
        edge_lists_ = std::vector<EdgeList>(size_vertices_);
    }

    /**
     * Clone the adjacency list.
     */
    void Clone(AdjacencyList* adjacency_list) const {
        assert(adjacency_list);
        assert(this != adjacency_list);

        adjacency_list->clear();
        adjacency_list->size_vertices_ = size_vertices_;
        adjacency_list->size_edges_ = size_edges_;
        adjacency_list->edge_lists_ = std::vector<EdgeList>(size_vertices_);

        // Allocate the edges.
        adjacency_list->edges_.resize(size_edges_);
        for (int i = 0; i < size_edges_; ++i) {
            adjacency_list->edges_[i] = adjacency_list->edges_pool_.Allocate();
        }

        // Clone the edges.
        for (int i = 0; i < size_edges_; ++i) {
            const Edge* e = edges_[i];
            Edge* e1 = adjacency_list->edges_[i];

            // First, copy the non-pointer data.
            *(e1) = *(e);

            // Second, copy the pointers.
            e1->twin_ = e->twin_ ? adjacency_list->edges_[e->twin_->id_] : NULL;

            // Finally, insert the edge into EdgeList.
            adjacency_list->edge_lists_[e->source()].push_back(e1);
        }

        for (BaseVectorPropertyMap* p : edge_properties_) {
            p->clear();
            p->resize(size_edges_);
        }
    }

    /**
     * Insert a one-way edge.
     *
     * @return the pointer to the new edge.
     */
    Edge* InsertOneWayEdge(int source, int target) {
        assert(0 <= source && source < size_vertices_);
        assert(0 <= target && target < size_vertices_);

        Edge* edge = edges_pool_.Allocate();
        edge->source_ = source;
        edge->target_ = target;
        edge->twin_   = NULL;
        edge->id_     = size_edges_;

        edges_.push_back(edge);
        edge_lists_[source].push_back(edge);
        ++size_edges_;

        for (BaseVectorPropertyMap* p : edge_properties_) {
            p->push_back();
        }

        return edge;
    }

    /**
     * Insert a tow-way edge.
     *
     * @return the iterator to the new edge from source to target.
     */
    Edge* InsertTwoWayEdge(int source, int target) {
        Edge* e1 = InsertOneWayEdge(source, target);
        Edge* e2 = InsertOneWayEdge(target, source);
        e1->twin_ = e2;
        e2->twin_ = e1;
        return e1;
    }

    /**
     * Erase the two-way edge from AdjacencyList.
     */
    void EraseTwoWayEdge(Edge* e) {
        EraseOneWayEdge(e);
        if (e->twin_) {
            EraseOneWayEdge(e->twin_);
        }
    }

    /**
     * Erase the one-way edge from AdjacencyList.
     */
    void EraseOneWayEdge(Edge* e) {
        assert(e->id_ >= 0 && e->id_ < size_edges_);

        edges_[e->id_] = edges_.back();
        edges_[e->id_]->id_ = e->id_;
        edges_.pop_back();
        edge_lists_[e->source_].erase(EdgeList::Iterator(e));

        if (e->twin_) {
            e->twin_->twin_ = NULL;
        }
        --size_edges_;
        edges_pool_.Free(e);

        for (BaseVectorPropertyMap* p : edge_properties_) {
            p->swap(e->id_, size_edges_);
            p->pop_back();
        }
    }

    /**
     * Find the pointer to the first edge equal to (source, target). Or return
     * NULL if no edge is found.
     */
    Edge* FindEdge(int source, int target) {
        assert(source >= 0 && source < size_vertices_);
        assert(target >= 0 && target < size_vertices_);

        for (Edge& e : edge_lists_[source]) {
            if (e.target_ == target) return &e;
        }

        return NULL;
    }

    /**
     * Find the pointer to the first edge equal to (source, target). Or return
     * NULL if no edge is found.
     */
    const Edge* FindEdge(int source, int target) const {
        assert(source >= 0 && source < size_vertices_);
        assert(target >= 0 && target < size_vertices_);

        for (const Edge& e : edge_lists_[source]) {
            if (e.target_ == target) return &e;
        }

        return NULL;
    }

    /**
     * Clear all edges.
     */
    void clear() {
        size_vertices_ = 0;
        size_edges_ = 0;
        edge_lists_.clear();
        edges_.clear();
        edges_pool_.clear();
    }

    bool empty()        const { return size_vertices_ == 0; }
    int size_vertices() const { return size_vertices_; }
    int size_edges()    const { return size_edges_; }

    // Access functions.
    const std::vector<EdgeList>& edge_lists() const { return edge_lists_;    }
    std::vector<EdgeList>& edge_lists()             { return edge_lists_;    }
    const EdgeList& edge_list(int i)          const { return edge_lists_[i]; }
    EdgeList& edge_list(int i)                      { return edge_lists_[i]; }
    const Edge* edge(int index)               const { return edges_[index];  }
    Edge* edge(int index)                           { return edges_[index];  }
    std::vector<Edge*>& edges()                     { return edges_;         }

protected:
    int size_vertices_;                // The number of vertices.
    int size_edges_;                   // The number of edges.
    std::vector<EdgeList> edge_lists_; // The edge lists.
    std::vector<Edge*> edges_;         // The edges of graph.
    ObjectPool<Edge> edges_pool_;      // Memory pool for edges.

    // The edge properties container, it used to store the various typed edge
    // properties.
    // Note that AdjacencyList dose not handle the Edge properties, so it dose
    // not need to free the memory here.
    std::vector<BaseVectorPropertyMap*> edge_properties_;
};

} // namespace cl

#endif // UTIL_LIST_ADJACENCY_LIST_H_
