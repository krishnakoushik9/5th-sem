package com.krsna.project.demo.dto;

import java.util.List;

public record ChatResponse(List<Choice> choices) {
}