import fs from 'fs';
import path from 'path';
import * as shiki from 'shiki';

interface QuizCodeSnippet {
  path: string; // Relative path like "quizzes/long-method-quiz-1/snippet.cpp"
  language: string;
  html?: string; // To be populated with highlighted code
}

interface QuizOption {
  id: string;
  text: string;
}

export interface QuizData {
  id: string;
  smellId: string;
  title: string;
  question: string;
  codeSnippet?: QuizCodeSnippet;
  quizType: string;
  options: QuizOption[];
  correctAnswer: string;
  explanation: string;
}

let highlighter: shiki.Highlighter;

async function getShikiHighlighter() {
  if (!highlighter) {
    highlighter = await shiki.createHighlighter({
      themes: ['github-dark'], // Or your preferred theme
      langs: ['cpp', 'c', 'json', 'bash']
    });
  }
  return highlighter;
}

export async function getQuizData(quizId: string): Promise<QuizData | null> {
  const quizDataPath = path.join(process.cwd(), 'src', 'content', 'quizzes', quizId, 'data.json');
  if (!fs.existsSync(quizDataPath)) {
    console.error(`Quiz data file not found: ${quizDataPath}`);
    return null;
  }

  try {
    const fileContents = fs.readFileSync(quizDataPath, 'utf8');
    const data = JSON.parse(fileContents) as QuizData;

    if (data.codeSnippet && data.codeSnippet.path) {
      // Note: data.codeSnippet.path is relative to 'src/content', e.g. "quizzes/quiz-id/snippet.cpp"
      // It should be used directly to join with 'src/content'
      const codeFilePath = path.join(process.cwd(), 'src', 'content', data.codeSnippet.path);
      
      if (fs.existsSync(codeFilePath)) {
        const rawCode = fs.readFileSync(codeFilePath, 'utf8');
        const shiki = await getShikiHighlighter();
        data.codeSnippet.html = shiki.codeToHtml(rawCode, { lang: data.codeSnippet.language as any, theme: 'github-dark' });
      } else {
        console.error(`Code snippet file not found: ${codeFilePath}`);
        data.codeSnippet.html = '<p>Code snippet file not found.</p>';
      }
    }
    return data;
  } catch (error) {
    console.error(`Error loading quiz data for ${quizId}:`, error);
    return null;
  }
}

// Function to get all quiz IDs (useful for generating static paths for quizzes later)
export async function getAllQuizIds() {
  const quizzesDirectory = path.join(process.cwd(), 'src', 'content', 'quizzes');
  if (!fs.existsSync(quizzesDirectory)) {
    return [];
  }
  const quizFolders = fs.readdirSync(quizzesDirectory, { withFileTypes: true })
    .filter(dirent => dirent.isDirectory())
    .map(dirent => dirent.name);
  return quizFolders;
}
