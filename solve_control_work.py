#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Скрипт для розв'язання задач контрольних робіт з лінійної алгебри та аналітичної геометрії
"""

import numpy as np
from numpy.linalg import inv, solve, det, norm
from math import sqrt, acos, degrees, radians, sin, cos, atan2
import sys
from typing import Union, Tuple

def solve_linear_system(A: np.ndarray, b: np.ndarray) -> Union[np.ndarray, str]:
    """
    Розв'язує систему лінійних рівнянь Ax = b
    
    Args:
        A: матриця коефіцієнтів розміру n×n
        b: вектор вільних членів розміру n
    
    Returns:
        x: розв'язок системи (вектор розміру n) або рядок з повідомленням про помилку
    """
    try:
        x = solve(A, b)
        return x
    except np.linalg.LinAlgError as e:
        return f"Помилка: {str(e)}"

def inverse_matrix(A):
    """
    Знаходить обернену матрицю
    
    Args:
        A: матриця (numpy array)
    
    Returns:
        A_inv: обернена матриця
    """
    try:
        if abs(det(A)) < 1e-10:
            return "Матриця вироджена, оберненої не існує"
        A_inv = inv(A)
        return A_inv
    except np.linalg.LinAlgError as e:
        return f"Помилка: {str(e)}"

def matrix_power(A, n):
    """
    Обчислює A^n
    
    Args:
        A: матриця (numpy array)
        n: степінь
    
    Returns:
        A^n
    """
    try:
        result = np.eye(A.shape[0])
        for _ in range(n):
            result = np.dot(result, A)
        return result
    except Exception as e:
        return f"Помилка: {str(e)}"

def dot_product(a, b):
    """Скалярний добуток векторів"""
    return np.dot(a, b)

def cross_product(a, b):
    """Векторний добуток векторів"""
    return np.cross(a, b)

def vector_angle(a, b):
    """
    Знаходить кут між векторами в градусах
    
    Args:
        a, b: вектори (numpy arrays)
    
    Returns:
        кут в градусах
    """
    dot = dot_product(a, b)
    norm_a = norm(a)
    norm_b = norm(b)
    if norm_a == 0 or norm_b == 0:
        return "Один з векторів нульовий"
    cos_angle = dot / (norm_a * norm_b)
    cos_angle = np.clip(cos_angle, -1.0, 1.0)
    angle_rad = acos(cos_angle)
    return degrees(angle_rad)

def distance_point_to_line_2d(point, line_coeffs):
    """
    Відстань від точки до прямої в 2D
    line_coeffs: [A, B, C] для рівняння Ax + By + C = 0
    """
    A, B, C = line_coeffs
    x0, y0 = point
    distance = abs(A * x0 + B * y0 + C) / sqrt(A**2 + B**2)
    return distance

def line_normal_form(A, B, C):
    """
    Зводить рівняння прямої Ax + By + C = 0 до нормального вигляду
    x*cos(alpha) + y*sin(alpha) - p = 0
    """
    norm_factor = sqrt(A**2 + B**2)
    if C > 0:
        norm_factor = -norm_factor
    
    A_norm = A / norm_factor
    B_norm = B / norm_factor
    C_norm = C / norm_factor
    
    p = -C_norm
    alpha = atan2(B_norm, A_norm)
    
    return {
        'normalized': f"{A_norm:.4f}x + {B_norm:.4f}y + {C_norm:.4f} = 0",
        'trigonometric': f"x*cos({degrees(alpha):.4f}°) + y*sin({degrees(alpha):.4f}°) - {p:.4f} = 0",
        'p': p,
        'alpha_deg': degrees(alpha)
    }

def plane_through_points(A, B, C):
    """
    Рівняння площини через три точки
    Повертає коефіцієнти [A, B, C, D] для Ax + By + Cz + D = 0
    """
    AB = B - A
    AC = C - A
    normal = cross_product(AB, AC)
    
    if norm(normal) < 1e-10:
        return "Точки лежать на одній прямій"
    
    D = -dot_product(normal, A)
    return np.array([normal[0], normal[1], normal[2], D])

def plane_through_point_perpendicular_to_vector(point, vector):
    """
    Рівняння площини через точку перпендикулярно до вектора
    """
    A, B, C = vector
    D = -dot_product(vector, point)
    return np.array([A, B, C, D])

def plane_parallel_to_plane_through_point(point, plane_coeffs):
    """
    Площина паралельна заданій площині через точку
    plane_coeffs: [A, B, C, D] для Ax + By + Cz + D = 0
    """
    A, B, C, D = plane_coeffs
    new_D = -(A * point[0] + B * point[1] + C * point[2])
    return np.array([A, B, C, new_D])

def distance_between_parallel_planes(plane1, plane2):
    """
    Відстань між двома паралельними площинами
    plane1, plane2: [A, B, C, D]
    """
    A1, B1, C1, D1 = plane1
    A2, B2, C2, D2 = plane2
    
    norm_factor = sqrt(A1**2 + B1**2 + C1**2)
    if norm_factor == 0:
        return "Площини не визначені"
    
    distance = abs(D1 - D2) / norm_factor
    return distance

def are_planes_perpendicular(plane1, plane2):
    """
    Перевіряє чи перпендикулярні площини
    """
    A1, B1, C1, _ = plane1
    A2, B2, C2, _ = plane2
    
    normal1 = np.array([A1, B1, C1])
    normal2 = np.array([A2, B2, C2])
    
    dot = dot_product(normal1, normal2)
    return abs(dot) < 1e-10

def are_planes_parallel(plane1, plane2):
    """
    Перевіряє чи паралельні площини
    """
    A1, B1, C1, _ = plane1
    A2, B2, C2, _ = plane2
    
    normal1 = np.array([A1, B1, C1])
    normal2 = np.array([A2, B2, C2])
    
    cross = cross_product(normal1, normal2)
    return norm(cross) < 1e-10

def line_through_point_parallel_to_vector(point, vector):
    """
    Канонічне рівняння прямої через точку паралельно вектору
    """
    x0, y0 = point
    m, n = vector
    return f"(x - {x0})/{m} = (y - {y0})/{n}"

def line_through_point_perpendicular_to_vector(point, vector):
    """
    Рівняння прямої через точку перпендикулярно до вектора
    """
    x0, y0 = point
    A, B = vector
    C = -(A * x0 + B * y0)
    return f"{A}x + {B}y + {C} = 0"

def line_through_two_points_2d(A, B):
    """
    Рівняння прямої через дві точки в 2D
    """
    x1, y1 = A
    x2, y2 = B
    
    if x2 == x1:
        return f"x = {x1}"
    
    k = (y2 - y1) / (x2 - x1)
    b = y1 - k * x1
    
    if b >= 0:
        return f"y = {k:.4f}x + {b:.4f}"
    else:
        return f"y = {k:.4f}x - {abs(b):.4f}"

def ellipse_canonical(focus_distance, major_axis):
    """
    Канонічне рівняння еліпса
    focus_distance: відстань між фокусами (2c)
    major_axis: велика вісь (2a)
    """
    c = focus_distance / 2
    a = major_axis / 2
    b = sqrt(a**2 - c**2)
    
    return f"x²/{a**2:.4f} + y²/{b**2:.4f} = 1"

def ellipse_from_eccentricity(focus_distance, eccentricity):
    """
    Канонічне рівняння еліпса з ексцентриситетом
    """
    c = focus_distance / 2
    a = c / eccentricity
    b = sqrt(a**2 - c**2)
    
    return f"x²/{a**2:.4f} + y²/{b**2:.4f} = 1"

def hyperbola_canonical(focus_distance, major_semiaxis):
    """
    Канонічне рівняння гіперболи
    focus_distance: відстань між фокусами (2c)
    major_semiaxis: велика піввісь (a)
    """
    c = focus_distance / 2
    a = major_semiaxis
    b = sqrt(c**2 - a**2)
    
    return f"x²/{a**2:.4f} - y²/{b**2:.4f} = 1"

def hyperbola_from_eccentricity(focus_distance, eccentricity):
    """
    Канонічне рівняння гіперболи з ексцентриситетом
    """
    c = focus_distance / 2
    a = c / eccentricity
    b = sqrt(c**2 - a**2)
    
    return f"x²/{a**2:.4f} - y²/{b**2:.4f} = 1"

def hyperbola_from_minor_axis(focus_distance, minor_axis):
    """
    Канонічне рівняння гіперболи з малою віссю
    """
    c = focus_distance / 2
    b = minor_axis / 2
    a = sqrt(c**2 - b**2)
    
    return f"x²/{a**2:.4f} - y²/{b**2:.4f} = 1"

def hyperbola_from_asymptotes_and_vertices(asymptote_slope, vertex_distance):
    """
    Канонічне рівняння гіперболи з асимптотами та відстанню між вершинами
    asymptote_slope: кутовий коефіцієнт асимптоти (b/a)
    vertex_distance: відстань між вершинами (2a)
    """
    a = vertex_distance / 2
    b = a * asymptote_slope
    
    return f"x²/{a**2:.4f} - y²/{b**2:.4f} = 1"

def parabola_canonical_symmetric_OX(point):
    """
    Канонічне рівняння параболи симетричної відносно OX через точку
    """
    x, y = point
    if x == 0 and y == 0:
        return "y² = 0"
    
    if y == 0:
        return "y² = 0"
    
    p = y**2 / (4 * abs(x))
    if x < 0:
        return f"y² = -{4*p:.4f}x"
    else:
        return f"y² = {4*p:.4f}x"

def parabola_canonical_symmetric_OY(point):
    """
    Канонічне рівняння параболи симетричної відносно OY через точку
    """
    x, y = point
    if x == 0 and y == 0:
        return "x² = 0"
    
    if x == 0:
        return "x² = 0"
    
    p = x**2 / (4 * abs(y))
    if y < 0:
        return f"x² = -{4*p:.4f}y"
    else:
        return f"x² = {4*p:.4f}y"

def circle_center_radius(equation_coeffs):
    """
    Знаходить центр і радіус кола з рівняння x² + y² + Dx + Ey + F = 0
    equation_coeffs: [D, E, F]
    """
    D, E, F = equation_coeffs
    center_x = -D / 2
    center_y = -E / 2
    radius = sqrt(center_x**2 + center_y**2 - F)
    
    return {
        'center': (center_x, center_y),
        'radius': radius,
        'equation': f"(x - {center_x:.4f})² + (y - {center_y:.4f})² = {radius**2:.4f}"
    }

def circle_from_diameter_ends(A, B):
    """
    Рівняння кола з кінцями діаметра
    """
    center = ((A[0] + B[0]) / 2, (A[1] + B[1]) / 2)
    radius = sqrt((A[0] - B[0])**2 + (A[1] - B[1])**2) / 2
    
    return {
        'center': center,
        'radius': radius,
        'equation': f"(x - {center[0]:.4f})² + (y - {center[1]:.4f})² = {radius**2:.4f}"
    }

def ellipse_properties(equation):
    """
    Визначає властивості еліпса з канонічного рівняння x²/a² + y²/b² = 1
    equation: (a, b) або рядок виду "x²/100 + y²/64 = 1"
    """
    if isinstance(equation, tuple):
        a, b = equation
    else:
        import re
        match = re.search(r'x²/(\d+\.?\d*)\s*\+\s*y²/(\d+\.?\d*)\s*=\s*1', equation)
        if match:
            a = float(match.group(1))
            b = float(match.group(2))
        else:
            return "Некоректне рівняння"
    
    c = sqrt(abs(a**2 - b**2))
    if a > b:
        foci = [(-c, 0), (c, 0)]
        vertices = [(-a, 0), (a, 0), (0, -b), (0, b)]
        eccentricity = c / a
    else:
        foci = [(0, -c), (0, c)]
        vertices = [(-b, 0), (b, 0), (0, -a), (0, a)]
        eccentricity = c / a
    
    directrices = []
    if a > b:
        d = a / eccentricity
        directrices = [f"x = -{d:.4f}", f"x = {d:.4f}"]
    else:
        d = a / eccentricity
        directrices = [f"y = -{d:.4f}", f"y = {d:.4f}"]
    
    return {
        'major_axis': 2 * max(a, b),
        'minor_axis': 2 * min(a, b),
        'foci': foci,
        'vertices': vertices,
        'eccentricity': eccentricity,
        'directrices': directrices
    }

def hyperbola_properties(equation):
    """
    Визначає властивості гіперболи з канонічного рівняння x²/a² - y²/b² = 1
    """
    if isinstance(equation, tuple):
        a, b = equation
    else:
        import re
        match = re.search(r'x²/(\d+\.?\d*)\s*-\s*y²/(\d+\.?\d*)\s*=\s*1', equation)
        if match:
            a = float(match.group(1))
            b = float(match.group(2))
        else:
            return "Некоректне рівняння"
    
    c = sqrt(a**2 + b**2)
    foci = [(-c, 0), (c, 0)]
    vertices = [(-a, 0), (a, 0)]
    eccentricity = c / a
    asymptotes = [f"y = {b/a:.4f}x", f"y = -{b/a:.4f}x"]
    
    return {
        'foci': foci,
        'vertices': vertices,
        'eccentricity': eccentricity,
        'asymptotes': asymptotes
    }

def parabola_properties(equation):
    """
    Визначає властивості параболи
    """
    import re
    if 'y²' in equation:
        match = re.search(r'y²\s*=\s*([+-]?)(\d+\.?\d*)x', equation)
        if match:
            sign = match.group(1)
            p = float(match.group(2)) / 4
            if sign == '-':
                p = -p
            focus = (p, 0)
            directrix = f"x = -{p:.4f}"
            return {'focus': focus, 'directrix': directrix}
    elif 'x²' in equation:
        match = re.search(r'x²\s*=\s*([+-]?)(\d+\.?\d*)y', equation)
        if match:
            sign = match.group(1)
            p = float(match.group(2)) / 4
            if sign == '-':
                p = -p
            focus = (0, p)
            directrix = f"y = -{p:.4f}"
            return {'focus': focus, 'directrix': directrix}
    
    return "Некоректне рівняння"

def print_solution(variant_num, task_num, solution):
    """Виводить розв'язок задачі"""
    print(f"\n{'='*60}")
    print(f"Варіант {variant_num}, Завдання {task_num}")
    print(f"{'='*60}")
    print(solution)
    print(f"{'='*60}\n")

def solve_variant_1():
    """Розв'язує варіант 1"""
    print("\n" + "="*60)
    print("Варіант 1")
    print("="*60)
    
    # Завдання 1: Система рівнянь
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -3, 1], [4, 2, 1], [4, -5, 0]])
    b1 = np.array([-7, -1, -5])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    # Завдання 2: Обернена матриця
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, 3, 2], [2, 5, 4], [3, 7, 5]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    # Завдання 3: Векторні операції
    print("\n3) Векторні операції:")
    a = np.array([0, 2, 6])
    b = np.array([2, 4, -1])
    
    result1 = 5 * a - 2 * b
    print(f"5a - 2b = {result1}")
    
    result2 = dot_product(a, 3 * b)
    print(f"a·(3b) = {result2:.4f}")
    
    result3 = cross_product(2 * a, b)
    print(f"(2a) × b = {result3}")
    
    angle = vector_angle(a, 2 * b)
    print(f"Кут між a і 2b: {angle:.4f}°")
    
    # Завдання 4: Відстань та площина
    print("\n4) Відстань та площина:")
    point_A = np.array([-2, 3])
    line_coeffs = [3, -4, -2]
    dist = distance_point_to_line_2d(point_A, line_coeffs)
    print(f"Відстань від A(-2, 3) до прямої 3x - 4y - 2 = 0: {dist:.4f}")
    
    A_3d = np.array([3, -1, 2])
    B_3d = np.array([4, 1, -1])
    C_3d = np.array([2, 0, -2])
    plane = plane_through_points(A_3d, B_3d, C_3d)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    # Завдання 5: Еліпс
    print("\n5) Канонічне рівняння еліпса:")
    ellipse_eq = ellipse_canonical(8, 10)
    print(ellipse_eq)

def solve_variant_2():
    """Розв'язує варіант 2"""
    print("\n" + "="*60)
    print("Варіант 2")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[5, 8, 2], [3, -2, 6], [2, 5, -1]])
    b1 = np.array([2, -7, -5])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, -1, -1], [2, 0, 3], [1, 1, 0]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    A = np.array([4, -5, 7])
    B = np.array([7, -3, 1])
    C = np.array([1, -9, 7])
    AB = B - A
    BC = C - B
    AC = C - A
    
    result1 = dot_product(5 * AB + BC, AB)
    print(f"(5AB + BC)·AB = {result1:.4f}")
    
    result2 = cross_product(AB, BC)
    print(f"AB × BC = {result2}")
    
    angle = vector_angle(AB, AC)
    print(f"Кут між AB і AC: {angle:.4f}°")
    
    print("\n4) Нормальний вигляд та площина:")
    line_coeffs = [4, -3, -20]
    normal = line_normal_form(*line_coeffs)
    print(f"Нормальний вигляд: {normal['normalized']}")
    
    A_3d = np.array([2, 1, -1])
    B_3d = np.array([3, -1, 2])
    AB_vec = B_3d - A_3d
    plane = plane_through_point_perpendicular_to_vector(A_3d, AB_vec)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Парабола:")
    parabola_eq = parabola_canonical_symmetric_OX(np.array([-1, 3]))
    print(parabola_eq)

def solve_variant_3():
    """Розв'язує варіант 3"""
    print("\n" + "="*60)
    print("Варіант 3")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -2, 1], [3, 2, 2], [2, -1, 1]])
    b1 = np.array([2, -2, 1])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[3, -4, 5], [2, -3, 1], [3, -5, -1]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([0, -1, 1])
    b = np.array([1, 4, 2])
    
    result1 = dot_product(4 * a, b)
    print(f"(4a)·b = {result1:.4f}")
    
    result2 = 3 * cross_product(a, -b)
    print(f"3(a × (-b)) = {result2}")
    
    angle = vector_angle(5 * a - 2 * b, b)
    print(f"Кут між 5a-2b і b: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([1, 7])
    s = np.array([3, 5])
    line_eq = line_through_point_parallel_to_vector(A_2d, s)
    print(f"Рівняння прямої: {line_eq}")
    
    point_3d = np.array([2, -2, 2])
    plane_coeffs = np.array([1, -2, -3, 0])
    plane = plane_parallel_to_plane_through_point(point_3d, plane_coeffs)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Коло:")
    circle = circle_center_radius([5, 2, -1])
    print(f"Центр: {circle['center']}, Радіус: {circle['radius']:.4f}")

def solve_variant_4():
    """Розв'язує варіант 4"""
    print("\n" + "="*60)
    print("Варіант 4")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, 3, 1], [1, -1, -1], [3, 4, 1]])
    b1 = np.array([5, 1, 6])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[4, 0, 1], [3, 0, 1], [1, 1, 1]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([0, -1, 1])
    b = np.array([1, 4, 2])
    
    result1 = dot_product(3 * a + 2 * b, b)
    print(f"(3a + 2b)·b = {result1:.4f}")
    
    result2 = 2 * cross_product(a, b)
    print(f"2(a × b) = {result2}")
    
    angle = vector_angle(a + b, b - a)
    print(f"Кут між a+b і b-a: {angle:.4f}°")
    
    print("\n4) Пряма та площини:")
    A_2d = np.array([-3, 1])
    B_2d = np.array([7, 8])
    line_eq = line_through_two_points_2d(A_2d, B_2d)
    print(f"Рівняння прямої: {line_eq}")
    
    plane1 = np.array([1, 3, -5, -1])
    plane2 = np.array([3, -4, 5, 2])
    are_perp = are_planes_perpendicular(plane1, plane2)
    print(f"Площини перпендикулярні: {are_perp}")
    
    print("\n5) Гіпербола:")
    hyperbola_eq = hyperbola_canonical(8, 5)
    print(hyperbola_eq)

def solve_variant_5():
    """Розв'язує варіант 5"""
    print("\n" + "="*60)
    print("Варіант 5")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -4, 3], [2, -4, 3], [3, -5, 2]])
    b1 = np.array([1, 3, 2])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, -1, 1], [0, 3, -1], [0, 2, 1]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([4, 3, -1])
    b = np.array([0, 2, 6])
    
    result1 = 7 * dot_product(a, -b)
    print(f"7(a·(-b)) = {result1:.4f}")
    
    result2 = 2 * cross_product(a, -3 * b)
    print(f"2(a × (-3b)) = {result2}")
    
    angle = vector_angle(2 * a, b + a)
    print(f"Кут між 2a і b+a: {angle:.4f}°")
    
    print("\n4) Пряма та площини:")
    A_2d = np.array([3, 5])
    s = np.array([1, 7])
    line_eq = line_through_point_perpendicular_to_vector(A_2d, s)
    print(f"Рівняння прямої: {line_eq}")
    
    plane1 = np.array([4, -3, 2, -1])
    plane2 = np.array([8, -6, 4, 7])
    are_par = are_planes_parallel(plane1, plane2)
    print(f"Площини паралельні: {are_par}")
    
    print("\n5) Коло:")
    circle = circle_center_radius([0, 0, 0])
    print(f"Центр: {circle['center']}, Радіус: {circle['radius']:.4f}")

def solve_variant_6():
    """Розв'язує варіант 6"""
    print("\n" + "="*60)
    print("Варіант 6")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[3, -5, 6], [-2, 4, 3], [3, 2, 1]])
    b1 = np.array([-1, 0, -5])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[2, 3, 2], [1, -2, 3], [3, 4, 1]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([3, -8, 2])
    b = np.array([0, -7, 5])
    
    result1 = dot_product(a, 5 * b)
    print(f"a·(5b) = {result1:.4f}")
    
    result2 = 2 * cross_product(a, -b)
    print(f"2(a × (-b)) = {result2}")
    
    angle = vector_angle(-2 * a, b - a)
    print(f"Кут між -2a і b-a: {angle:.4f}°")
    
    print("\n4) Відстані:")
    M = np.array([-1, 2])
    line_coeffs = [2, -1, -1]
    dist = distance_point_to_line_2d(M, line_coeffs)
    print(f"Відстань від M(-1, 2) до прямої: {dist:.4f}")
    
    plane1 = np.array([1, -2, -1, -1])
    plane2 = np.array([1, -2, -1, 2])
    dist_planes = distance_between_parallel_planes(plane1, plane2)
    print(f"Відстань між площинами: {dist_planes:.4f}")
    
    print("\n5) Гіпербола:")
    props = hyperbola_properties((9, 16))
    print(f"Ексцентриситет: {props['eccentricity']:.4f}")
    print(f"Асимптоти: {props['asymptotes']}")

def solve_variant_7():
    """Розв'язує варіант 7"""
    print("\n" + "="*60)
    print("Варіант 7")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[3, 2, 1], [2, -4, -5], [3, 3, 1]])
    b1 = np.array([5, -5, -4])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, -2, 3], [2, 1, -1], [1, 3, 4]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([7, 3, 4])
    b = np.array([1, 0, 6])
    
    result1 = dot_product(a + b, a - b)
    print(f"(a+b)·(a-b) = {result1:.4f}")
    
    result2 = cross_product(a, -3 * b)
    print(f"a × (-3b) = {result2}")
    
    angle = vector_angle(a - b, b + 2 * a)
    print(f"Кут між a-b і b+2a: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([-2, 1])
    angle_deg = 30
    print("Рівняння прямої через точку під кутом 30° (потрібні додаткові дані)")
    
    M1 = np.array([2, 1, 1])
    M2 = np.array([-1, 2, 1])
    M3 = np.array([2, -2, 1])
    plane = plane_through_points(M1, M2, M3)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Еліпс:")
    ellipse_eq = ellipse_from_eccentricity(24, 3/4)
    print(ellipse_eq)

def solve_variant_8():
    """Розв'язує варіант 8"""
    print("\n" + "="*60)
    print("Варіант 8")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[3, 1, -1], [2, 1, -5], [2, -2, 1]])
    b1 = np.array([6, 5, 2])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, 2, 3], [1, 3, 5], [1, 2, 4]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([-4, 1, 6])
    b = np.array([-1, 0, -1])
    
    result1 = dot_product(a, 5 * b)
    print(f"a·(5b) = {result1:.4f}")
    
    result2 = -3 * cross_product(a, b)
    print(f"-3(a × b) = {result2}")
    
    angle = vector_angle(4 * a, -3 * b)
    print(f"Кут між 4a і -3b: {angle:.4f}°")
    
    print("\n4) Нормальний вигляд та площина:")
    line_coeffs = [3, -4, -1]
    normal = line_normal_form(*line_coeffs)
    print(f"Нормальний вигляд: {normal['normalized']}")
    
    M = np.array([1, 2, -1])
    print("Площина через точку з відрізками на осях (потрібні додаткові дані)")
    
    print("\n5) Коло:")
    circle = circle_center_radius([-8, 6, 0])
    print(f"Центр: {circle['center']}, Радіус: {circle['radius']:.4f}")

def solve_variant_9():
    """Розв'язує варіант 9"""
    print("\n" + "="*60)
    print("Варіант 9")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -2, 1], [2, 3, 1], [3, -2, -1]])
    b1 = np.array([-2, -1, 3])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[0, -2, 1], [4, 3, 0], [1, -2, -2]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    A = np.array([-4, 5, 3])
    B = np.array([7, 3, -1])
    C = np.array([1, 5, -4])
    AB = B - A
    BC = C - B
    AC = C - A
    
    result1 = dot_product(AB + BC, AB)
    print(f"(AB + BC)·AB = {result1:.4f}")
    
    result2 = cross_product(AB, AC)
    print(f"AB × AC = {result2}")
    
    angle = vector_angle(AB, BC)
    print(f"Кут між AB і BC: {angle:.4f}°")
    
    print("\n4) Відстань та площина:")
    M0 = np.array([1, 2, -1])
    print("Відстань від точки до прямої (потрібні додаткові дані)")
    
    A_3d = np.array([0, 1, -2])
    B_3d = np.array([3, 5, 0])
    C_3d = np.array([-2, 0, 1])
    plane = plane_through_points(A_3d, B_3d, C_3d)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Еліпс:")
    props = ellipse_properties((10, 8))
    print(f"Довжини осей: велика = {props['major_axis']:.4f}, мала = {props['minor_axis']:.4f}")
    print(f"Фокуси: {props['foci']}")
    print(f"Вершини: {props['vertices']}")
    print(f"Ексцентриситет: {props['eccentricity']:.4f}")
    print(f"Директриси: {props['directrices']}")

def solve_variant_10():
    """Розв'язує варіант 10"""
    print("\n" + "="*60)
    print("Варіант 10")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -4, 3], [2, -4, 3], [3, -5, 2]])
    b1 = np.array([1, 3, 2])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, -1, 1], [0, 3, -1], [0, 2, 1]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    A = np.array([4, 0, 3])
    B = np.array([7, 2, -1])
    C = np.array([1, -5, 2])
    AB = B - A
    BC = C - B
    AC = C - A
    
    result1 = dot_product(2 * AB - BC, AB)
    print(f"(2AB - BC)·AB = {result1:.4f}")
    
    result2 = 3 * cross_product(AB, AC)
    print(f"3(AB × AC) = {result2}")
    
    angle = vector_angle(AB, AC)
    print(f"Кут між AB і AC: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([3, -5])
    s = np.array([-2, 7])
    line_eq = line_through_point_parallel_to_vector(A_2d, s)
    print(f"Рівняння прямої: {line_eq}")
    
    A_3d = np.array([2, 0, 0])
    B_3d = np.array([0, 0, 1])
    C_3d = np.array([0, -1, 0])
    plane = plane_through_points(A_3d, B_3d, C_3d)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Гіпербола:")
    hyperbola_eq = hyperbola_from_minor_axis(10, 8)
    print(hyperbola_eq)

def solve_variant_11():
    """Розв'язує варіант 11"""
    print("\n" + "="*60)
    print("Варіант 11")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[1, -1, 1], [2, 1, 0], [1, 1, -1]])
    b1 = np.array([0, 1, -2])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, -3, 2], [2, 1, -1], [3, 1, 1]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    A = np.array([4, 0, 3])
    B = np.array([3, -3, 1])
    C = np.array([1, 3, -2])
    AB = B - A
    BC = C - B
    AC = C - A
    
    result1 = dot_product(AB - BC, AB)
    print(f"(AB - BC)·AB = {result1:.4f}")
    
    result2 = cross_product(AB, BC)
    print(f"AB × BC = {result2}")
    
    angle = vector_angle(AB, AC)
    print(f"Кут між AB і AC: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([2, -3])
    print("Рівняння прямої паралельної заданій (потрібні додаткові дані)")
    
    plane_coeffs = np.array([1, -2, 2, 6])
    normal = line_normal_form(plane_coeffs[0], plane_coeffs[1], plane_coeffs[3])
    print(f"Нормальний вигляд площини: {normal['normalized']}")
    
    print("\n5) Гіпербола:")
    hyperbola_eq = hyperbola_from_asymptotes_and_vertices(5/12, 48)
    print(hyperbola_eq)

def solve_variant_12():
    """Розв'язує варіант 12"""
    print("\n" + "="*60)
    print("Варіант 12")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -3, 0], [1, 2, -1], [3, -3, -1]])
    b1 = np.array([-1, 2, -1])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[3, 2, 2], [1, 3, 1], [5, 3, 4]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([1, -2, 3])
    b = np.array([7, 0, 1])
    c = np.array([-1, 5, 8])
    
    result1 = dot_product(2 * a - b, c)
    print(f"(2a - b)·c = {result1:.4f}")
    
    result2 = 3 * cross_product(c, b)
    print(f"3(c × b) = {result2}")
    
    angle = vector_angle(2 * a, c)
    print(f"Кут між 2a і c: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([3, 5])
    s = np.array([1, 7])
    line_eq = line_through_point_perpendicular_to_vector(A_2d, s)
    print(f"Рівняння прямої: {line_eq}")
    
    A_3d = np.array([2, -3, 5])
    print("Площина з рівними відрізками на осях (потрібні додаткові дані)")
    
    print("\n5) Гіпербола:")
    hyperbola_eq = hyperbola_from_eccentricity(20, 5/3)
    print(hyperbola_eq)

def solve_variant_13():
    """Розв'язує варіант 13"""
    print("\n" + "="*60)
    print("Варіант 13")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, 2, 1], [2, -3, 1], [5, -4, 3]])
    b1 = np.array([1, 1, -3])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Матриця A³:")
    A2 = np.array([[3, 2, 2], [1, 3, 1], [5, 3, 4]])
    A2_cubed = matrix_power(A2, 3)
    print("A³ =")
    print(A2_cubed)
    
    print("\n3) Векторні операції:")
    a = np.array([-3, 0, 0])
    b = np.array([3, 4, -2])
    c = np.array([7, -3, -1])
    
    result1 = norm(a)
    print(f"|a| = {result1:.4f}")
    
    result2 = dot_product(b, c)
    print(f"b·c = {result2:.4f}")
    
    result3 = 3 * cross_product(c, b)
    print(f"3(c × b) = {result3}")
    
    angle = vector_angle(b, c)
    print(f"Кут між b і c: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([-4, 2])
    line_coeffs = [2, -3, 5]
    line_eq = line_through_point_perpendicular_to_vector(A_2d, line_coeffs[:2])
    print(f"Рівняння прямої: {line_eq}")
    
    A_3d = np.array([2, 1, -1])
    B_3d = np.array([3, -1, 2])
    AB_vec = B_3d - A_3d
    plane = plane_through_point_perpendicular_to_vector(A_3d, AB_vec)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Еліпс:")
    props = ellipse_properties((4, 5))
    print(f"Фокуси: {props['foci']}")
    print(f"Ексцентриситет: {props['eccentricity']:.4f}")
    print(f"Директриси: {props['directrices']}")

def solve_variant_14():
    """Розв'язує варіант 14"""
    print("\n" + "="*60)
    print("Варіант 14")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[5, 8, 2], [3, -2, 6], [2, 5, -1]])
    b1 = np.array([2, -7, -5])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[3, -4, 5], [2, -3, 1], [3, -5, -1]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    b = np.array([-3, -4, 1])
    c = np.array([-7, 3, -1])
    
    result1 = dot_product(3 * b, 2 * c)
    print(f"(3b)·(2c) = {result1:.4f}")
    
    result2 = cross_product(b, c)
    print(f"b × c = {result2}")
    
    angle = vector_angle(-3 * b, c + 5 * b)
    print(f"Кут між -3b і c+5b: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    P = np.array([2, 3])
    print("Пряма через точку з рівними відрізками (потрібні додаткові дані)")
    
    A_3d = np.array([-2, -1, 1])
    B_3d = np.array([-3, 1, -4])
    AB_vec = B_3d - A_3d
    plane = plane_through_point_perpendicular_to_vector(A_3d, AB_vec)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Коло:")
    center = (-1, -4)
    radius = sqrt(5)
    print(f"Рівняння кола: (x + 1)² + (y + 4)² = {radius**2:.4f}")

def solve_variant_15():
    """Розв'язує варіант 15"""
    print("\n" + "="*60)
    print("Варіант 15")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -1, 1], [2, 1, 4], [2, -3, -2]])
    b1 = np.array([0, 4, -2])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Матриця A³:")
    A2 = np.array([[3, -4, -2], [2, 0, 1], [5, 9, 1]])
    A2_cubed = matrix_power(A2, 3)
    print("A³ =")
    print(A2_cubed)
    
    print("\n3) Векторні операції:")
    b = np.array([1, -4, 2])
    c = np.array([5, -4, 1])
    
    result1 = dot_product(c - 3 * b, c)
    print(f"(c - 3b)·c = {result1:.4f}")
    
    result2 = cross_product(c, b)
    print(f"c × b = {result2}")
    
    angle = vector_angle(2 * b, c)
    print(f"Кут між 2b і c: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    line_coeffs = [2, -3, 6]
    k = -line_coeffs[0] / line_coeffs[1]
    print(f"Кутовий коефіцієнт прямої: {k:.4f}")
    
    A_3d = np.array([3, 1, 2])
    B_3d = np.array([2, -1, 3])
    a_vec = np.array([3, -1, 4])
    plane = plane_through_point_perpendicular_to_vector(A_3d, a_vec)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Парабола:")
    parabola_eq = parabola_canonical_symmetric_OY(np.array([-4, -2]))
    print(parabola_eq)

def solve_variant_16():
    """Розв'язує варіант 16"""
    print("\n" + "="*60)
    print("Варіант 16")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, 3, 1], [1, -1, -1], [3, 4, 1]])
    b1 = np.array([5, 1, 6])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, 3, 2], [2, 5, 4], [3, 7, 5]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([-1, 7, 2])
    b = np.array([-5, 4, 1])
    
    result1 = norm(a + b)**2
    print(f"|a + b|² = {result1:.4f}")
    
    result2 = cross_product(a, b)
    print(f"a × b = {result2}")
    
    print("\n4) Нормальний вигляд та площина:")
    line_coeffs = [4, -3, 20]
    normal = line_normal_form(*line_coeffs)
    print(f"Нормальний вигляд: {normal['normalized']}")
    
    A_3d = np.array([1, 4, 2])
    B_3d = np.array([-2, 1, 3])
    a_vec = np.array([3, -1, 4])
    plane = plane_through_point_perpendicular_to_vector(A_3d, a_vec)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Коло:")
    A_2d = np.array([1, 3])
    B_2d = np.array([9, 9])
    circle = circle_from_diameter_ends(A_2d, B_2d)
    print(f"Рівняння кола: {circle['equation']}")

def solve_variant_17():
    """Розв'язує варіант 17"""
    print("\n" + "="*60)
    print("Варіант 17")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -4, 3], [2, -4, 3], [3, -5, 2]])
    b1 = np.array([1, 3, 2])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[3, 2, 2], [1, 3, 1], [5, 3, 4]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([-3, 3, 1])
    b = np.array([2, -2, 5])
    
    result1 = dot_product(a, b)
    print(f"a·b = {result1:.4f}")
    
    result2 = cross_product(a, b)
    print(f"a × b = {result2}")
    
    angle = vector_angle(a + b, a - b)
    print(f"Кут між a+b і a-b: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([1, -3])
    line_coeffs = [0, 1, 6]
    line_eq = line_through_point_perpendicular_to_vector(A_2d, [1, 3])
    print(f"Рівняння прямої: {line_eq}")
    
    A_3d = np.array([1, -4, 2])
    B_3d = np.array([-2, 1, 3])
    C_3d = np.array([-3, -1, 4])
    plane = plane_through_points(A_3d, B_3d, C_3d)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Парабола:")
    props = parabola_properties("y² = 4x")
    print(f"Фокус: {props['focus']}")
    print(f"Директриса: {props['directrix']}")

def solve_variant_18():
    """Розв'язує варіант 18"""
    print("\n" + "="*60)
    print("Варіант 18")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -1, 1], [2, 1, 4], [2, -3, -2]])
    b1 = np.array([0, 4, -2])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, -1, -1], [2, 0, 3], [1, 1, 0]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([4, 3, -1])
    b = np.array([0, 2, 6])
    
    result1 = dot_product(a, b)
    print(f"a·b = {result1:.4f}")
    
    result2 = cross_product(a, b)
    print(f"a × b = {result2}")
    
    angle = vector_angle(2 * a - b, a + b)
    print(f"Кут між 2a-b і a+b: {angle:.4f}°")
    
    print("\n4) Точка перетину та площина:")
    line1 = [2, -3, -3]
    line2 = [4, -3, 7]
    A_line = np.array([[line1[0], line1[1]], [line2[0], line2[1]]])
    b_line = np.array([-line1[2], -line2[2]])
    intersection = solve_linear_system(A_line, b_line)
    print(f"Точка перетину: ({intersection[0]:.4f}, {intersection[1]:.4f})")
    
    point_3d = np.array([2, -2, 2])
    plane_coeffs = np.array([1, -2, -3, 0])
    plane = plane_parallel_to_plane_through_point(point_3d, plane_coeffs)
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Гіпербола:")
    hyperbola_eq = hyperbola_from_eccentricity(16, 3/2)
    print(hyperbola_eq)

def solve_variant_19():
    """Розв'язує варіант 19"""
    print("\n" + "="*60)
    print("Варіант 19")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, -2, 1], [3, 2, 2], [2, -1, 1]])
    b1 = np.array([2, -2, 1])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Обернена матриця:")
    A2 = np.array([[1, -1, 1], [2, -4, 3], [1, -5, 8]])
    A2_inv = inverse_matrix(A2)
    print("A^(-1) =")
    print(A2_inv)
    
    print("\n3) Векторні операції:")
    a = np.array([4, 3, -1])
    b = np.array([0, 2, 6])
    
    result1 = dot_product(a, 3 * b)
    print(f"a·(3b) = {result1:.4f}")
    
    result2 = 2 * cross_product(a, b)
    print(f"2(a × b) = {result2}")
    
    angle = vector_angle(-2 * a, b)
    print(f"Кут між -2a і b: {angle:.4f}°")
    
    print("\n4) Пряма та площини:")
    A_2d = np.array([-1, 6])
    s = np.array([3, -5])
    line_eq = line_through_point_parallel_to_vector(A_2d, s)
    print(f"Рівняння прямої: {line_eq}")
    
    plane1 = np.array([4, -3, 2, -1])
    plane2 = np.array([8, -6, 4, 7])
    are_par = are_planes_parallel(plane1, plane2)
    print(f"Площини паралельні: {are_par}")
    
    print("\n5) Гіпербола:")
    hyperbola_eq = hyperbola_from_eccentricity(16, 3/2)
    print(hyperbola_eq)

def solve_variant_20():
    """Розв'язує варіант 20"""
    print("\n" + "="*60)
    print("Варіант 20")
    print("="*60)
    
    print("\n1) Система рівнянь:")
    A1 = np.array([[2, 2, 1], [2, -3, 1], [5, -4, 3]])
    b1 = np.array([1, 1, -3])
    x1 = solve_linear_system(A1, b1)
    print(f"Розв'язок: x = {x1[0]:.4f}, y = {x1[1]:.4f}, z = {x1[2]:.4f}")
    
    print("\n2) Матриця A³:")
    A2 = np.array([[3, -1, 2], [2, -4, 3], [5, -7, 8]])
    A2_cubed = matrix_power(A2, 3)
    print("A³ =")
    print(A2_cubed)
    
    print("\n3) Векторні операції:")
    a = np.array([9, 3, -1])
    b = np.array([1, 2, -4])
    
    result1 = dot_product(2 * a, b)
    print(f"(2a)·b = {result1:.4f}")
    
    result2 = cross_product(a, b)
    print(f"a × b = {result2}")
    
    angle = vector_angle(a, 4 * b)
    print(f"Кут між a і 4b: {angle:.4f}°")
    
    print("\n4) Пряма та площина:")
    A_2d = np.array([1, 2])
    print("Пряма під кутом 45° (потрібні додаткові дані)")
    
    point_3d = np.array([-2, -2, 2])
    plane_coeffs = np.array([1, -2, -3, 0])
    plane = plane_through_point_perpendicular_to_vector(point_3d, plane_coeffs[:3])
    print(f"Рівняння площини: {plane[0]:.4f}x + {plane[1]:.4f}y + {plane[2]:.4f}z + {plane[3]:.4f} = 0")
    
    print("\n5) Коло:")
    circle = circle_center_radius([4, -2, -20])
    print(f"Канонічне рівняння: {circle['equation']}")

if __name__ == "__main__":
    variants = {
        1: solve_variant_1,
        2: solve_variant_2,
        3: solve_variant_3,
        4: solve_variant_4,
        5: solve_variant_5,
        6: solve_variant_6,
        7: solve_variant_7,
        8: solve_variant_8,
        9: solve_variant_9,
        10: solve_variant_10,
        11: solve_variant_11,
        12: solve_variant_12,
        13: solve_variant_13,
        14: solve_variant_14,
        15: solve_variant_15,
        16: solve_variant_16,
        17: solve_variant_17,
        18: solve_variant_18,
        19: solve_variant_19,
        20: solve_variant_20
    }
    
    if len(sys.argv) > 1:
        variant = int(sys.argv[1])
        if variant in variants:
            variants[variant]()
        else:
            print(f"Варіант {variant} не існує. Доступні варіанти: 1-20")
    else:
        print("Використання: python solve_control_work.py <номер_варіанту>")
        print("Приклад: python solve_control_work.py 1")
        print("\nДоступні варіанти: 1-20")

