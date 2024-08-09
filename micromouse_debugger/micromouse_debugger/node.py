#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import pygame
import sys

# Define some colors
GRAY = (200, 200, 200)
RED = (255, 0, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

CELL_SIZE = 50  # Size of each cell

class MicromouseDebugger(Node):
    def __init__(self):
        super().__init__('micromouse_debugger')
        self.subscription = self.create_subscription(
            String,
            'micromouse/debug_log',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.get_logger().info('MicromouseDebugger node has been initialized.')
        
        # Initialize Pygame
        pygame.init()
        self.screen = pygame.display.set_mode((800, 800))
        pygame.display.set_caption("Micromouse Grid Debugger")
        self.clock = pygame.time.Clock()
        self.grid = {}

    def listener_callback(self, msg):
        grid_str = msg.data
        self.get_logger().info('Received map string.')
        print(grid_str)


def main(args=None):
    rclpy.init(args=args)
    
    node = MicromouseDebugger()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
