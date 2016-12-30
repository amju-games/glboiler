// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "scene_description.h"

const camera& scene_description::get_camera() const
{
  return m_camera;
}

const scene_node& scene_description::get_root_node() const
{
  return *m_root_node;
}

void scene_description::set_root_node(p_scene_node node)
{
  m_root_node = node;
}


/*
scene_node_id scene_description::add_node(p_scene_node node)
{
  m_nodes.push_back(node);
  return m_nodes.size();
}

void scene_graph::add_connection(scene_node_id node_1, scene_node_id node_2)
{
  if (m_connections.size() <= node_1)
  {
    // When we resize, increase by more than the bare minimum necessary,
    //  as we are likely to want to add more nodes. I.e. same reasoning
    //  as when we resize in vector::push_back.
    const float RESIZE_FACTOR = 1.5f;  

    // Add 1: if node_1 is zero, we want to have space for at least 
    //  1 element.
    int new_size = static_cast<int>(node_1 * RESIZE_FACTOR) + 1; 
    m_connections.resize(new_size);
  }
  m_connections[node_1].push_back(node_2);
}
*/

