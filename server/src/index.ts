import Koa from 'koa'
import Router from '@koa/router'
import bodyParser from 'koa-bodyparser'
import { Database } from './database'
import { port, elasticsearchNode } from './config'

// eslint-disable-next-line @typescript-eslint/no-floating-promises
;(async () => {
  const app = new Koa()
  const router = new Router()

  const db = new Database(elasticsearchNode)
  await db.open()

  router.post('/post', async (ctx, next) => {
    await db.addRecord(new Date(), ctx.request.body)
    ctx.body = ''
  })

  app
    .use(bodyParser())
    .use(router.routes())
    .use(router.allowedMethods())
    .listen(port, () => {
      console.log(`Server listening at http://127.0.0.1:${port}/`)
    })
})()
