// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "int_graph.h"

TEST(int_graph, create)
{
  int_graph ig;
  ASSERT_TRUE(ig.is_empty());
}

TEST(int_graph, add_connection)
{
  int_graph ig;
  ig.add_connection(3, 5);
  ASSERT_FALSE(ig.is_empty());

  auto connections = ig.get_connections(1);
  ASSERT_EQ(connections.size(), 0);

  connections = ig.get_connections(3);
  ASSERT_EQ(connections.size(), 1);
  ASSERT_EQ(connections[0], 5);

  connections = ig.get_connections(5);
  ASSERT_EQ(connections.size(), 0);
}


